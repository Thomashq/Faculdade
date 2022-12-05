const database = require('../../db')

class userStudent{
    constructor(StudentId, Name, City, Education, Email, Password){
        this.StudentId = StudentId;
        this.Name = Name;
        this.City = City;
        this.Education = Education;
        this.Email = Email;
        this.Password = Password;
    }
}