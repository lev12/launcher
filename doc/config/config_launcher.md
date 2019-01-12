# Launcher config
File path './/application_config.cfg'

## Content
width = 800 (unsigned short)  
Width of the application at startup. Value in pixels (corrent value round from 1 to 65,535).

height = 600 (unsigned short)  
Height of the application at startup. Value in pixels (corrent value round from 1 to 65,535).

fullScrean = false (bool)  
Full Screan of the application at startup. Value 'true' or 'false'

language = EN (string)  
The application language is set. Letter abbreviations according to [ISO 639-1 (code language)](https://ru.wikipedia.org/wiki/%D0%9A%D0%BE%D0%B4%D1%8B_%D1%8F%D0%B7%D1%8B%D0%BA%D0%BE%D0%B2).

startPage = 0 (unsigned short)
Id page to start

ipServer = http://electrical-simulator.ru (string)  
Ip address or domain server.

portServer = 80 (unsigned short)  
Server port (corrent value round from 1 to 65,535).

log = 0 (unsigned short)  
State logging  

- 0 - no logging  
- 1 - logging  
- 2 - logging and send to server

logPath = .//log (string)  
Path to folder save log. Path start with './/'  

countFileLog = 10 (unsigned short)  
Number of logs saved. If 0 then the logs will not be deleted.