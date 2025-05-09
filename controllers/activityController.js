const Activity = require('../models/Activity');

exports.createActivity = async (req, res) => {
    const { title, description, location, date_time } = req.body;

    const activity = new Activity({
        title,
        description,
        location,
        date_time,
        createdBy: req.user._id
    });

    await activity.save();
    res.status(201).json({ message: 'Activity created successfully', activity });
};

exports.getActivities = async (req, res) => {
    try {
        const activities = await Activity.find();
        res.status(200).json(activities);
    } catch (error) {
        res.status(500).json({ message: 'Error fetching activities' });
    }
};