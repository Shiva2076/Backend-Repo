const Booking = require('../models/Booking');
const Activity = require('../models/Activity');

exports.bookActivity = async (req, res) => {
    const { activity_id } = req.body;

    const activity = await Activity.findById(activity_id);
    if (!activity) {
        return res.status(404).json({ message: 'Activity not found' });
    }

    const booking = new Booking({
        user_id: req.user._id,
        activity_id
    });

    await booking.save();
    res.status(201).json({ message: 'Activity booked successfully', booking });
};

exports.getMyBookings = async (req, res) => {
    try {
        const bookings = await Booking.find({ user_id: req.user._id }).populate('activity_id');
        res.status(200).json(bookings);
    } catch (error) {
        res.status(500).json({ message: 'Error fetching bookings' });
    }
};