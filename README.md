# LieLife

##### in English
## It's graphic branch
### General information

SFML is a graphic library that provides tools for simple graphics creation, such as for video games.
But this library does not have tools for convenient and simple creation of a normal program.
Therefore, in this branch, tools are beging developed for simple construction of the graphical interface of a regular program.

The "organization style" of objects is inspired by the standard Python graphics library tkinter.


### Development
This project does not intend to implement a completely similar toolkit with tkinter, only:
- [x] *Widget*  - base class (widget), whith has implementation of all common widget capabilities;
- [x] *Label*   - caption that displays the text on the screen;
- [x] *Button*  - button that to treggers events;
- [ ] *Entry*   - field in which you can enter information;
- [ ] *PopInfo (pop-up information)*  - pop-up window with additional information (for example, to display explanations for terms);
- [x] *system of binding functions to widgets*  - binding of functions that will be call when an event occurs with widgets;
- [ ] *grid-placement*  - dividing the available window space into rows, columns and placing widgets along them (not by coordinates).




##### на Українській 
## Це graphic вітка
### Загальні відомості

SFML - графічна бібліотека, що надає існтрументи для простого утворення графіки, наприклад для відеоігор.
Але ця бібліотека не має інструментів для зручного та простого створення звичайної програми.
Тому в цій вітці розроблюється інструменти, для простого побудування графічного інтерфейсу звичайної програми.

"Стиль організації" об'єктів надиханий стандартною графічною бібліотекою tkinter із Python.


### Розробка
Цей проект не має наміру реалізувати повністю аналогічний інструментарій з tkinter, лише:
- [x] *Widget*  - базовий клас (віджет), що має реалізацію усіх загальних можливостей віджетів;
- [x] *Label*   - підпис, що виводить текст на екран;
- [x] *Button*  - кнопка, головне завдання котрої запускати події;
- [ ] *Entry*   - поле, в яку можна вводити інформацію;
- [ ] *PopInfo (pop-up information)*  - виникаюча вікно, з додатковою інформацією (наприклад для виведення пояснень до термінів);
- [x] *система прив'язки функцій до віджетів* - прив'язка функцій, що будуть викликатися при виниканні події з віджетами;
- [ ] *grid-розміщення* - розбиття доступного простору вікна на рядки і колонки та розміщення віджетів по ним (а не по координатам).

