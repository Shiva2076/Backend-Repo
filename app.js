const express = require('express');
const mongoose = require('mongoose');
const connectDB = require('./config/db')
const dotenv = require('dotenv');
const authRoutes = require('./routes/authRoutes');
const activityRoutes = require('./routes/activityRoutes');
const bookingRoutes = require('./routes/bookingRoutes');

dotenv.config();
const app = express();
app.use(express.json());

// Connect to database
connectDB();

// Remove duplicate mongoose connection
// mongoose.connect(process.env.MONGO_URI, { useNewUrlParser: true, useUnifiedTopology: true })
//    .then(() => console.log("MongoDB connected"))
//    .catch(err => console.log(err));

// Add a root route handler
app.get('/', (req, res) => {
  res.send({
    message: 'Activity Booking API is running',
    version: '1.0.0',
    endpoints: {
      auth: '/api/auth',
      activities: '/api/activities',
      bookings: '/api/bookings'
    }
  });
});

// API routes
app.use('/api/auth', authRoutes);
app.use('/api/activities', activityRoutes);
app.use('/api/bookings', bookingRoutes);

// Error handling middleware
app.use((req, res) => {
  res.status(404).json({ message: 'Route not found' });
});

app.use((err, req, res, next) => {
  console.error(err.stack);
  res.status(500).json({ message: 'Server error', error: err.message });
});

const PORT = process.env.PORT || 5000;
app.listen(PORT, () => console.log(`Server is running on port ${PORT}`));

module.exports = app; // Export for testing purposes
