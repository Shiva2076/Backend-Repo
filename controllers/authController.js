const User = require('../models/User');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const joi = require('joi');

exports.register = async (req, res) => {
    const schema = joi.object({
        name: joi.string().required(),
        email: joi.string().email().required(),
        phone: joi.string().required(),
        password: joi.string().min(6).required()
    });

    const { error } = schema.validate(req.body);
    if (error) return res.status(400).send(error.details[0].message);
    
    const { name, email, phone, password } = req.body;

    const existingUser = await User.findOne({ email });
    if (existingUser) return res.status(400).send("User already exists");

    const hashedPassword = await bcrypt.hash(password, 10);
    const user = new User({ name, email, phone, password: hashedPassword });
    await user.save();
    
    res.status(201).send({ message: "User registered successfully" });
};

exports.login = async (req, res) => {
    const schema = joi.object({
        email: joi.string().email().required(),
        password: joi.string().required()
    });

    const { error } = schema.validate(req.body);
    if (error) return res.status(400).send(error.details[0].message);

    const user = await User.findOne({ email: req.body.email });
    if (!user) return res.status(400).send("Invalid email or password");

    const validPassword = await bcrypt.compare(req.body.password, user.password);
    if (!validPassword) return res.status(400).send("Invalid email or password");

    const token = jwt.sign({ _id: user._id }, process.env.JWT_SECRET, { expiresIn: '1h' });
    res.header('auth-token', token).send({ token });
};