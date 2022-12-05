const sequelize = require('sequelize');

const database = new sequelize('TRABALHOWEB', 'sa', '4sd129A4',
{
    dialect: 'mssql', host: 'localhost', port: 1433
});

database.sync();

module.exports = database;