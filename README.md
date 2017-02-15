# TeamCreator
Given a file (rugby_athletes.json in this directory), containing a JSON 
encoded list of Squads and Athletes, plus a squad ID, output an entirely 
new squad of 15 for a rugby team using the following criteria
   
   - No players in the team should be injured
   - The team should be a valid Rugby Union team - (2 props, 1 hooker, 2 
   locks, 2 flankers, 1 Number Eight, 1 Scrum Half, 1 Out Half, 2 Centres, 2 
   Wingers, 1 Full Back)
   - The output should contain at least the following - squad name, squad 
   ID and a list of the players with their position

The program is using RapidJson to parse the JSON file and all the rapidjsn
headers are in the include folder.


