const express = require('express');
const router = express.Router();
const userStudentController = require('../controllers/userStudentController.js')

router.get('/ListUserStudent', userStudentController.List);
router.post('/CreateUserStudent', userStudentController.Create);
module.exports = router;