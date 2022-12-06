const {Model, DataTypes} = require('sequelize')
const database = require('../../db')
const shema = ""

class userStudent extends Model{
    static init(sequelize){
        super.init({
            StudentID:
            {
                type:DataTypes.INTEGER,
                autoIncrement: true,
                allowNull: false,
                primaryKey:true,
            },
            NAME:
            {
                type:DataTypes.STRING,
                allowNull: false,
            },
            CITY:
            {
                type:DataTypes.STRING,
                allowNull: false,
            },
            EDUCATION:
            {
                type:DataTypes.STRING,
                allowNull: false,   
            },
            EMAIL:
            {
                type:DataTypes.STRING,
                allowNull: false,
            },
            PASSWORD:
            {
                type:DataTypes.STRING,
                allowNull: false,
            },
        },{
            sequelize, modelName: 'userStudent'
        })
    }
}

module.exports = userStudent;
