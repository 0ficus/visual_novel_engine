## Visual Novel Engine

Данный проект представляет собой движок/библиотеку, разработанную для языка программирования C++, для удобного создания визуальных новелл.

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)

## Описание проекта

Данный движок является удобным инструментом для создания визуальных новелл с сюжетом любой сложности. 

Задача разработчика: описать сюжет в виде графа при помощи предоставленных движком структур; при этом, работа с графикой со стороны разработчика минимальна, он может даже не знать, что предоставленные функции — обертка над SFML, все удобно автоматизированно.

Движок предоставляет разработчику широкий набор объектов, которыми он может воспользоваться (расположены в [visual_novel_engine/engine/objects/user_objects](https://github.com/0ficus/visual_novel_engine/tree/main/engine/objects/user_objects)):

  * Actions — класс, описывающий выбор действия в визуальной новелле.
  * DialogueBox — диалоговое окно для отображение речи персонажей.
  * FrameSlots — слоты для размещения персонажей на игровой сцене.
  * Frame — сцена, которая позволяет удобно работать с вышеописанными объектами, как с единым целым.
  * Chapter — глава сюжета. Может быть интерпретирована как вершина графа, которая описывает конкретный эпизод сюжета.
  * Script — набор глав, который может быть интерпретирован, как оптимизированная по памяти матрица смежности графа, то есть, данный класс содержит ребра графа.
  * VisualNovel — обработчик вышеописанного графа, составленного разработчиком: данный класс реализует автоматизацию игрового процесса, задает дизайн главного меню и т.п.

Подробнее о данных объектах и их эксплуатации можно прочитать в [документации](https://github.com/0ficus/visual_novel_engine/blob/main/documentation.md).

## Установка

1. Клонировать репозиторий:
   ```bash
   git clone https://github.com/0ficus/visual_novel_engine.git

2. Удовлетворить зависимости: может потребоваться установка [SFML](https://www.sfml-dev.org/download/sfml/2.6.1/) для вашей ОС.

## Использование

Хранить вспомогательные данные по типу изображений, музыкальных файлов, шрифтов и т.п. рекомендуется в [visual_novel_engine/game/game_data](https://github.com/0ficus/visual_novel_engine/tree/main/game/game_data). 

Разработку игрового приложения рекомендуется вести в [visual_novel_engine/game](https://github.com/0ficus/visual_novel_engine/tree/main/game).

Руководство по использованию функций, структур данных, которые предоставляются движком можно прочитать в [документации](https://github.com/0ficus/visual_novel_engine/blob/main/documentation.md).

## Лицензия

Этот проект лицензирован под MIT License — подробности см. в файле [LICENSE](https://github.com/0ficus/visual_novel_engine/blob/main/LICENSE).
