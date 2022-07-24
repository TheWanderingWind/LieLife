# LieLife

##### in English
## General information

The goal of progect development is to training and demonstrate programming skills. The progect is NOT commercial.

The progect is inspired by Jonson Conway's cage automaton called **Conway's Game of Life**, 1970.
**Game of Life** aims to simulate the behavior of cells depending on the presence of living cells around them (you can learn more [here](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life))

LieLife aims to make a more believable simulation of life and demonstrate the principle of evolution.
The world will also consist of some splace where a cell can be placed.
Each cell will have so-called genome is a sequence of codes, each of wthich indicates a command that the cell will carry out
(for example, the photosynthesis code will tell the cell to get energy from the sun).
Sometimes the cell will divide, creating a copy of itself in the free space near it.
Sometimes a mutation will happen - the new cell will have a slightly changes genome, which can completely change the behevior of the cell.

The progect is not intended to demonstrate plausible simulations. Just to make a demonstration of the evolution process.


## Development

The development uses the graphic libery [SFML](https://www.sfml-dev.org/index.php) for C++. The progect developed in C++.

The develompment of the progect is generally divided into 2 main parts:
- develompment graphic part
- develompment of simulation implementation

The main parts will be developed in the respective branch [*graphic*](https://github.com/TheWanderingWind/LieLife/tree/graphic) and *source*[^1] (perhaps additional functionality will be developed in additional branches) 

##### на Українському
## Загальні відомості

Ціль розробки проекту є відточення та демонстрація навичок програмування. Проект НЕ комерційний.

Проект надиханий клітковим автомату Джонсона Конвеєм під назвою **Гра «Життя»** (англ. Conway’s Game od Life) 1970 р.
**Гра «Життя»** має на меті моделювання поведінки клітин в залежності від наявності живих клітин навколо себе (більше можна дізнатися [тут](https://uk.wikipedia.org/wiki/Життя_(гра))).

LieLife має на меті зробити більш правдоподібну моделювання життя і продемонструвати принцип еволюції.
Світ так само буде складатися з деякого простору де може бути розміщена клітина.
Кожна клітина буде мати т. з. геном – послідовність кодів, кожна з котрих вказує на команду, яку буде виконувати клітина
(наприклад, код фотосинтезу буде вказувати клітині отримати енергію від сонця).
Раз в деякий час клітина буде ділитися, створюючи свою копію у вільному просторі біля себе.
Інколи буде траплятися мутація – нова клітина буде мати трішки змінений геном, із-за чого може повністю змінитись поведінка клітини.

Проект не має на меті продемонструвати правдоподібне моделювання. Лише зробити показову демонстрацію процесу еволюції.


## Розробка
При розробці використовується графічна бібліотека [SFML](https://www.sfml-dev.org/index.php) для C++. Сам проект розроблюється на C++.

Розробка проекту загалом поділена на 2 головні частики:
- розробка графічної частини 
- розробка реалізації моделювання

Головні частині будуть розроблюватись у відповідних вітках [*graphic*](https://github.com/TheWanderingWind/LieLife/tree/graphic) та *source*[^2] (можливо додатковий функціонал буде розроблюватись у додаткових вітках)


[^1]: Not yet created
[^2]: Поки що не створенно 
