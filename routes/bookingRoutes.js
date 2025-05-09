const express = require('express');
const router = express.Router();
const bookingController = require('../controllers/bookingController');
const auth = require('../middleware/auth');

router.post('/', auth, bookingController.bookActivity); 
router.get('/', auth, bookingController.getMyBookings); 

module.exports = router;