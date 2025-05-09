const Activity = require('../models/Activity');
const Joi = require('joi');

exports.createActivity = async (req, res) => {
    const schema = Joi.object({
        title: Joi.string().min(3).max(100).required(),
        description: Joi.string().min(3).max(500).required(),
        location: Joi.string().min(3).max(100).required(),
        date_time: Joi.date().required()
    });

    const { error } = schema.validate(req.body);
    if (error) {
        return res.status(400).send(error.details[0].message);
    }

    const { title, description, location, date_time } = req.body;

    const activity = new Activity({
        title,
        description,
        location,
        date_time,
        createdBy: req.user ? req.user._id : null 
    });

    await activity.save();
    res.status(201).json({ message: 'Activity created successfully', activity });
};

exports.getActivities = async (req, res) => {
    try {
        const activities = await Activity.find();
        res.status(200).json(activities);
    } catch (err) {
        res.status(500).json({ message: 'Server Error', error: err.message });
    }
};
