const people_button = document.getElementById("people_button");
const num_people_input = document.getElementById("num_people");
const people_section = document.getElementById("info_section");
const parse_button = document.getElementById("parse_button");

people_button.addEventListener("click", function() {
   const num_people = Number(num_people_input.value);
   people_section.innerHTML = "";

   for (let i = 0; i < num_people; i++) {
      const row = document.createElement("div");

      row.innerHTML = `
         <label>Person ${i + 1} Name:</label>
         <input class="name_input" type="text" placeholder="Name">

         <label> Email:</label>
         <input class="email_input" type="text" placeholder="Email">
      `;
      people_section.appendChild(row);
   }
});

parse_button.addEventListener("click", async function() {
   const people = [];
   for (const row of people_section.children) {
      const name = row.getElementsByClassName("name_input")[0].value;
      const email = row.getElementsByClassName("email_input")[0].value;
      people.push({
         name: name,
         email: email
      });
   }
   const num_people = Number(num_people_input.value);

   const response = await fetch("/info-submitted", {
      method: "POST",

      headers: {"Content-Type": "application/json"},

      body: JSON.stringify({
         num_people: num_people,
         people: people
      })
   });

   const result = await response.json();

   console.log(result);
});
