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
    },
    async Create(req, res){
        try{
            const result = await userStudent.create({
                NAME: req.body.NAME,
                CITY: req.body.CITY,
                EDUCATION: req.body.EDUCATION,
                EMAIL: req.body.EDUCATION,
                PASSWORD: req.body.PASSWORD
            });
            return console.log("Produto adicionado com sucesso: ", result);
        }catch(erro){
            return console.log("Não foi possível criar: ", erro);
        }
    }

}