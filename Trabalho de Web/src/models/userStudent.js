const Sequelize = require('sequelize')
const database = require('../../db')
const shema = ""
class userStudent extends Sequelize.Model{}

module.exports = sequelize =>userStudent.init(
    {
        StudentID:
        {
            type:sequelize.INTERGER,
            autoIncrement: true,
            allowNull: false,
            primaryKey:true,
        },
        NAME:
        {
            type:sequelize.STRING,
            allowNull: false,
        },
        CITY:
        {
            type:sequelize.STRING,
            allowNull: false,
        },
        EDUCATION:
        {
            type:sequelize.STRING,
            allowNull: false,   
        },
        EMAIL:
        {
            type:sequelize.STRING,
            allowNull: false,
        },
        PASSWORD:
        {
            type:sequelize.STRING,
            allowNull: false,
        },
        sequelize:database, modelName: 'userStudent', shema
    }
)
