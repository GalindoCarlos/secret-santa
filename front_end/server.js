require("dotenv").config();

const path = require("path")

// Used to access filesystem library
const fs = require("fs");

// Allows for external programs to run
const { execFile } = require("child_process");

// Used to create basic framework to make code simpler
const express = require("express");

// initalizes an app that uses this framework
const app = express();

// where the app can be accessed
const PORT = process.env.PORT || 3000;

// allows server to parse JSON files into Javascript objects
app.use(express.json());

// gets information to web-side
app.post("/info-submitted", function (request, result) {
   // tbd parsing request and writing to file
   let file_text = "";

   file_text += request.body.num_people + "\n";

   for (let i = 0; i < request.body.num_people; i++) {
      file_text += request.body.people[i].name + " " +
                   request.body.people[i].email + "\n";

   }

   fs.writeFileSync("info.txt", file_text);


   execFile("../choose", function (error, stdout, stderr) {
      if (error) {
         console.error(error);
         result.status(500).json({
            message: "Error creating assignments"
         });
         return;
      }
      if (stderr) {
         console.error(stderr);
      }

      execFile("python3", ["../emailing.py"], function (error, stdout, stderr) {
         if (error) {
            console.error(error);
            result.status(500).json({
               message: "Emails not sent successfully"
            });
            return;
         }
         console.log(stdout);

         if (stderr) {
            console.error(stderr);
         }

         result.json({
            message: "Emails successfully sent"
         });

      });
   });

});

// allows server to access files in current directory
app.use(express.static(__dirname));

// used to print message whenever Node is used to start this server
app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}`);
});
