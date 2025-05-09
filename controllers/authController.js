const User = require('../models/User');
const bcrypt = require('bcryptjs');
const jwt = require('jsonwebtoken');
const Joi = require('joi');

// Function for registering a user
exports.register = async (req, res) => {
    // Define validation schema
    const schema = Joi.object({
        name: Joi.string().min(3).max(30).required(),
        email: Joi.string().email().required(),
        phone: Joi.string().required(),
        password: Joi.string().min(6).required()
    });

    // Validate request body
    const { error } = schema.validate(req.body);
    if (error) {
        return res.status(400).send(error.details[0].message); // Return validation error message
    }
    
    const { name, email, phone, password } = req.body;

    // Check whether the user already exists
    const existingUser = await User.findOne({ email });
    if (existingUser) {
        return res.status(400).send("User already exists");
    }

    // Hash the user's password
    const hashedPassword = await bcrypt.hash(password, 10);

    // Create a new User instance with the hashed password
    const user = new User({ name, email, phone, password: hashedPassword });
    await user.save();
    
    res.status(201).send({ message: "User registered successfully" });
};

// Function for user login
exports.login = async (req, res) => {
    // Define login schema
    const schema = Joi.object({
        email: Joi.string().email().required(),
        password: Joi.string().required()
    });

    // Validate request body
    const { error } = schema.validate(req.body);
    if (error) {
        return res.status(400).send(error.details[0].message); // Return validation error message
    }

    const user = await User.findOne({ email: req.body.email });
    if (!user) {
        return res.status(400).send("Invalid email or password");
    }

    // Compare input password with hashed password
    const validPassword = await bcrypt.compare(req.body.password, user.password);
    if (!validPassword) {
        return res.status(400).send("Invalid email or password");
    }

    // Create and send the token
    const token = jwt.sign({ _id: user._id }, process.env.JWT_SECRET, { expiresIn: '1h' });
    res.header('auth-token', token).send({ token });
};