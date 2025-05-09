const express = require('express');
const router = express.Router();
const activityController = require('../controllers/activityController');

router.get('/', activityController.getActivities);

router.post('/', activityController.createActivity);

module.exports = router;
