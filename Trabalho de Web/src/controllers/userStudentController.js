const database = require('../../db.js');

const userStudent = require('../models/userStudent.js').userStudent;

module.exports = 
{
    async List(req, res){
        try{
            const result = await userStudent.findAll();
            return res.json(result);
        }catch(erro){
            return console.error("Erro ao listar : ", erro);
        }
    }


}