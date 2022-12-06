const sequelize = require('sequelize');
const user = require('./src/models/userStudent.js');

const database = new sequelize('TRABALHOWEB', 'sa', '*4sd129A4',
{
    dialect: 'mssql', host: 'localhost', port: 1433
});
user.init(database);
database.sync();

module.exports = database;