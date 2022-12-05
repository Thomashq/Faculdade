
const { Sequelize } = require('sequelize')
const database = require('../../db')
const shema = ""
class userStudent extends Sequelize.Model{}

userStudent.init(
    {
        StudentID:
        {
            type:Sequelize.INTERGER,
            autoIncrement: true,
            allowNull: false,
            primaryKey:true,
        },
        NAME:
        {
            type:Sequelize.STRING,
            allowNull: false,
        },
        CITY:
        {
            type:Sequelize.STRING,
            allowNull: false,
        },
        EDUCATION:
        {
            type:Sequelize.STRING,
            allowNull: false,   
        },
        EMAIL:
        {
            type:Sequelize.STRING,
            allowNull: false,
        },
        PASSWORD:
        {
            type:Sequelize.STRING,
            allowNull: false,
        },
        sequelize:database, modelName: 'userStudent', shema
    }
)
module.exports = userStudent;