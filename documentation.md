**ge::Action**

Пользовательский класс представляет собой выбор действия в игровом процессе, выбор которого определяет последовательность происходящих 
событий в сюжете визуальной новеллы. Имеет такие характеристики, как месторасположение (координаты в формате sf::Vector2f,
где первым параметром выступает значение по горизонтальной оси координат, вторым - по вертикальной оси координат, важно 
отметить, что координаты {0.; 0.} - это левый верхний угол, а координаты {1.; 1.} - правый нижний), внешний вид (то есть 
надпись в формате std::wstring) и точка перехода (название главы, к которой следует перейти после выбора данного 
действия в формате std::wstring).

Конструкторы:
    
    Action() // конструктор по умолчанию, координаты левого верхнего угла, пустая надпись, нет точки перехода
    
    Action(const sf::Vector2f &coords, std::wstring text, std::wstring chapter_name_to_go) // конструктор с необходимыми
                                                                                                для полноценной работы аргументами.
    
    Action(const Action &action) // конструктор копирования

    Action(Action &&action) noexcept // move-конструктор

При использовании конструктора с необходимыми аргументами проверяется, что координаты имеют правильный вид, то есть 
значение в множестве [0; 1] x [0; 1].

Операторы:

    Action &operator=(const Action &action) // оператор присваивания с помощью копирования 

    Action &operator=(Action &&action) noexcept // оператор присваивания с помощью move-конструкции

    bool operator==(const Action &action) const // оператор сравнения, возвращает true, если объекты совпадают, и false иначе

Методы: 

    [[nodiscard]] const sf::Vector2f &getCoords() const // возвращает относительные координаты

    [[nodiscard]] const std::wstring &getText() const // возвращает внешний вид действия

    [[nodiscard]] const std::wstring &getChapterNameToGo() const // возвращает точку перехода

    void setRelativeCoords(const sf::Vector2f &relative_coords) // устанавливает относительные координаты, проверяя их корректность

    void setText(const std::wstring &text) // устанавливает внешний вид действия

    void setChapterNameToGo(const std::wstring &chapter_name_to_go) // устанавливает точку перехода

---

**ge::DialogueBox**

Пользовательский класс представляет собой диалоговое окно. Имеет такие характеристики, как speaker (в формате std::wstring длиной не 
болкк 50 символов) и реплика (в формате std::wstring длиной не более 500 символов).

Конструкторы:

    DialogueBox() // конструктор по умолчанию, speaker и реплика инициализируются пустой строкой
 
    DialogueBox(const DialogueBox &other) // конструктор копирования

    DialogueBox(std::wstring speaker, std::wstring replica) // конструктор с необходимыми для полноценной работы 
                                                                                                        аргументами.

    DialogueBox(DialogueBox &&other) noexcept // move-конструктор

Операторы:

    DialogueBox &operator=(const DialogueBox &other) // оператор присваивания при помощи копирования

    DialogueBox &operator=(DialogueBox &&other) noexcept // оператор присваивания при помощи move-конструкции

    bool operator== (const DialogueBox& dialogue_box) const // оператор проверки равенства: возвращает true, если объекты 
                                                                равны, и false иначе.

    bool operator!= (const DialogueBox& dialogue_box) const; // оператор проверки неравенства: возвращает true, если 
                                                                объекты не равны, и false иначе.

Методы:

    void setReplica(const std::wstring &replica) // устанавливает реплику, проверяя, что ее длина не превышает 500 символов

    void setSpeaker(const std::wstring &speaker) // устанавливает speaker'a, проверяя, что его длина не превышает 50 символов

    [[nodiscard]] const std::wstring &getReplica() const // возвращает реплику

    [[nodiscard]] const std::wstring &getSpeaker() const // возвращает speaker'a

---

**ge::FrameSlots**

Пользовательский класс представляет собой слоты, в которых размещаются действующие в конкретном кадре персонажи. Имеет характеристики 
количество слотов (в формате unsigned int в диапазоне [0, 10]) и пути к картинкам, которые будут устанавливаться на 
сцене в качестве слотов (в формате std::vector<<std::string>> длина которого не превышает 10).

Конструкторы:

    FrameSlots() // конструктор по умолчанию, инициализирует количество слотов нулем и вектор путей остается пустой

    FrameSlots(const FrameSlots &frame_slots) // конструктор копирования

    FrameSlots(FrameSlots &&frame_slots) noexcept // move-конструктор

    explicit FrameSlots(const std::vector<std::string> &pictures_in_slots) // конструктор принимающий вектор путей и 
                                                                                проверяющий, что размер вектора не 
                                                                                превосходит 10.

Операторы:

    FrameSlots &operator=(const FrameSlots &frame_slots) // оператор присваивания при помощи копирования

    FrameSlots &operator=(FrameSlots &&frame_slots) noexcept // оператор присваивания при помощи move-конструкции

Методы:

    void setQuantityOfSlots(unsigned int quantity_of_slots) // устанавливает количество слотов

    void setPicturesInSlots(const std::vector<std::string> &pictures_in_slots) // устанавливает вектор путей

    [[nodiscard]] unsigned int getQuantityOfSlots() const // возвращает количество слотов

    [[nodiscard]] const std::vector<std::string> &getPicturesInSlots() const // возвращает вектор путей

---

**ge::Frame**

Пользоватеьлский класс представляет собой сцену/кадр, которая может содержать диалоговое окно, слоты с персонажами и выбор действий. 
Имеет такие харакетристики, как диалоговое окно (в формате ge::DialogueBox), путь к файлу, который будет использоваться 
для установки фона (в формате std::string), зависимость от выбора действий (в формате bool), набор действий для выбора
(в формате std::vector<<ge::Action>>) и слоты персонажей (в формате ge::FrameSlots).

Конструкторы:

    Frame() // конструктор по умолчанию, все поля инициализируются по умолчанию, за исключением зависимости от выбора 
                                                                                    действий, она инициализируется false.

    Frame(const Frame &scene) // констуктор копирования

    Frame(Frame &&scene) noexcept // move-конструктор

    Frame(DialogueBox dialogue_box, std::string background_file, FrameSlots slots) // конструктор без зависимости от 
                                                                                        выбора действий

    Frame(const std::vector<Action>& actions, std::string background_file, FrameSlots slots) // конструктор с 
                                                                                                зависимостью от выбора
                                                                                                действий.

Операторы:

    Frame &operator=(const Frame &scene) // оператор присваивания с помощью копирования

    Frame &operator=(Frame &&scene) noexcept // оператор присваивания с помощью move-конструкции

Методы:

    void setDialogueBox(const DialogueBox &dialogue_box) // устанавливает диалоговое окно

    void setBackground(const std::string &background_file) // устанавливает путь к фоновому изображению

    void setChoiceOfAction(bool choice_of_action) // устанавливает зависимость от выбора действий

    void setActions(const std::vector<Action> &actions) // устанавливает выбор действий

    void setSlots(const FrameSlots &scene_slots) // устанавливает слоты с действующими лицами

    const DialogueBox &getDialogueBox() const // возвращает диалоговое окно

    [[nodiscard]] const std::string &getBackgroundFile() const // возвращает путь к фоновому изображению

    [[nodiscard]] bool getChoiceOfAction() const // возвращает зависимость от выбора действий

    [[nodiscard]] const std::vector<Action> &getActions() const // возвращает список для выбора действий

    [[nodiscard]] const FrameSlots &getSlots() const // возвращает слоты с действующими лицами

---

**ge::Chapter**

Пользовательский класс представляет собой главу, то есть список кадров, которые последовательно воспроизводятся. Имеет такие 
характеристики, как название (в формате std::wstring) и список кадров (в формате std::vector<<ge::Frame>>).

Конструкторы:
    
    Chapter() // конструктор по умолчанию

    Chapter(const Chapter &chapter) // конструктор копирования

    Chapter(std::wstring chapter_name, const std::vector<Frame> &frames) // конструктор, принимающий все необходимые 
                                                                            аргументы для полноценной работы.

    Chapter(Chapter &&chapter) noexcept // move-конструктор

Операторы:
    
    Chapter &operator=(const Chapter &chapter) // оператор присваивания с помощью копирования

    Chapter &operator=(Chapter &&chapter) noexcept // оператор присваивания с помощью move-конструкции

Методы нет.

---

**ge::Script**

Пользовательская структура представляет собой хранилище глав, с помощью которого организуются переходы между ними. Имеет харакетристику 
список глав (в формате std::unordered_map<std::wstring, Chapter>).

Конструкторы:

    Script() // констурктор по умолчанию

    Script(const Script &script) // конструктор копирования

    explicit Script(const std::unordered_map<std::wstring, Chapter> &chapters) // констуктор от хранилища

    Script(Script &&script) noexcept // move-конструктор

Операторы:

    Script &operator=(const Script &script) // оператор присваивания с помощью копирования

    Script &operator=(Script &&script) noexcept // оператор присванивания с помощью move-конструкции

Методы:

    void addChapter(const std::wstring& name, const Chapter& chapter) // добавляет главу в хранилище

    bool eraseChapter(const std::wstring& name) // возвращает true, если главу удалось удалить, иначе false

---

**VisualNovel**

Пользовательский класс, запускающее само приложение с помощью использования вышеперечисленных классов и структур. Имеет 
такие характеристики, как игровые режими (в формате enum class GameMode, ниже подробнее), информация об авторах (в формате std::wstring), скрипт (в формате ge::Script), имя приложения
(в формате std::wstring), установленный игровой режим (в формате ge::GameMode) и стартовая глава (в формате std::wstring).

Конструкторы:

    VisualNovel() // конструктор по умолчанию, кроме имени приложения (оно инициализируется, как L"VisualNovel") и 
                                                            игрового режима (он инициализируется GameMode::MainMenu).

    VisualNovel(const VisualNovel &visual_novel) // конструктор копирования

    VisualNovel(VisualNovel &&visual_novel) noexcept // move-конструктор

    VisualNovel(std::wstring about_authors, Script script, std::wstring project_name, 
                std::wstring  name_start_chapter) // конструктор со всеми необходимыми для полноценной работы аргументами.

Операторов нет.

Методы:

    void setAboutAuthors(const std::wstring &about_authors) // установка информации об авторах

    void setScript(const Script &script) // установка скрипта

    void setProjectName(const std::wstring &project_name) // установка имени приложения

    void setNameStartChapter(const std::wstring& name_start_chapter) // установка стартовой главы

    const std::wstring &getAboutAuthors() // возвращает информацию об авторах

    const Script &getScript() // возвращает скрипт

    const std::wstring &getNameStartChapter() // возвращает имя стартовой главы

    bool run() // запускает приложение и возвращает true, если во время запуска не возникло ошибок, и false иначе.

---
