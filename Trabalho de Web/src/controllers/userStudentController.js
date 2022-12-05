const ModelStudent = require('../models/userStudent').userStudent;
const userTeatcher = require('../models/userTeatcher');

module.exports = 
{
    async List(req, res){
        try{
            const userStudents = await ModelStudent.findAll();
            return res.json(userStudents);
        }catch(erro){
            return console.error("Erro ao listar : ", erro);
        }
    }
}