#include "text.h"

#include <QKeyEvent>
#include <QRegularExpression>

#include "keyboard.h"

Text::Text(QWidget *parent)
    : QWidget(parent),
      layout(new QGridLayout()),
      keyboardLayout(English),
      offset(0) {
    setMaximumHeight(35 * kRowCount);
    setFocusPolicy(Qt::StrongFocus);
    grabKeyboard();
    setLayout(layout);
    layout->setSpacing(0);
    for (int i = 0; i < kRowCount; i++) {
        letters.push_back(QVector<Letter *>());
        for (int j = 0; j < kColumnCount; j++) {
            auto *letter = new Letter();
            letter->setFont(QFont("Noto Sans Mono"));
            layout->addWidget(letter, i, j);
            letters[i].push_back(letter);
        }
    }
    generateConverter();
    restart();
}

Text::~Text() {
    for (auto &row : letters) {
        for (Letter *letter : row) {
            delete letter;
        }
    }
}

QString Text::generate() {
    QMap<Layout, QVector<QString>> words{
        {English,
         {"the", "quick", "brown", "fox", "jumps", "over", "lazy", "dog",
          "hello", "world", "cat", "sun", "moon", "star", "tree", "house",
          "car", "road", "book", "pen", "water", "fire", "wind", "earth",
          "sky", "cloud", "rain", "snow", "flower", "grass", "leaf", "bird",
          "fish", "horse", "sheep", "cow", "milk", "bread", "cheese", "apple",
          "orange", "lemon", "table", "chair", "window", "door", "floor",
          "wall", "garden", "river", "mountain"}},
        {Russian,
         {"привет", "мир", "солнце", "луна", "звезда", "дерево", "дом",
          "машина", "дорога", "книга", "ручка", "вода", "огонь", "ветер",
          "земля", "небо", "облако", "дождь", "снег", "цветок", "трава",
          "лист", "птица", "рыба", "лошадь", "овца", "корова", "молоко",
          "хлеб", "сыр", "яблоко", "апельсин", "лимон", "стол", "стул",
          "окно", "дверь", "пол", "стена", "сад", "река", "гора", "друг",
          "семья", "работа", "школа", "университет", "город", "страна",
          "язык", "карандаш"}},
        {German,
         {"hallo", "welt", "sonne", "mond", "stern", "baum", "haus", "auto",
          "strasse", "buch", "stift", "wasser", "feuer", "wind", "erde",
          "himmel", "wolke", "regen", "schnee", "blume", "gras", "blatt",
          "vogel", "fisch", "pferd", "schaf", "kuh", "milch", "brot",
          "kaese", "apfel", "orange", "zitrone", "tisch", "stuhl", "fenster",
          "tuer", "boden", "decke", "wand", "garten", "fluss", "berg",
          "freund", "familie", "arbeit", "schule", "universitaet", "stadt",
          "land", "flugzeug"}},
        {French,
         {"bonjour", "monde", "soleil", "lune", "etoile", "arbre", "maison",
          "voiture", "route", "livre", "stylo", "eau", "feu", "vent", "terre",
          "ciel", "nuage", "pluie", "neige", "fleur", "herbe", "feuille",
          "oiseau", "poisson", "cheval", "mouton", "vache", "lait", "pain",
          "fromage", "pomme", "orange", "citron", "table", "chaise",
          "fenetre", "porte", "sol", "plafond", "mur", "jardin", "riviere",
          "montagne", "ami", "famille", "travail", "ecole", "universite",
          "ville", "pays", "nuage"}},
        {Arabic,
         {"مرحبا", "عالم", "شمس", "قمر", "نجم", "شجرة", "بيت", "سيارة",
          "طريق", "كتاب", "قلم", "ماء", "نار", "ريح", "ارض", "سماء",
          "سحاب", "مطر", "ثلج", "وردة", "عشب", "ورق", "طائر", "سمك",
          "حصان", "خروف", "بقرة", "حليب", "خبز", "جبن", "تفاح", "برتقال",
          "ليمون", "طاولة", "كرسي", "باب", "ارضية", "سقف", "جدار",
          "حديقة", "وادي", "جبل", "صديق", "عائلة", "عمل", "مدرسة",
          "جامعة", "مدينة", "بلد", "بحر"}},
        {Chinese,
         {"手", "拉", "水", "口", "山", "戈", "人", "心", "日", "尸",
          "木", "火", "土", "竹", "十", "大", "中", "重", "難", "金",
          "女", "月", "弓", "一", "手拉", "水口", "山戈", "人心", "日尸",
          "木火", "土竹", "十大", "中金", "女月", "弓一", "重難", "廿卜",
          "一口", "大中", "日土", "尸山", "木水", "火竹", "土十", "竹大",
          "十中", "手日", "拉尸", "水山", "戈口"}},
        {Belarusian,
         {"прывітанне", "свет", "сонца", "месяц", "зорка", "дрэва", "дом",
          "машына", "дарога", "кніга", "ручка", "вада", "агонь", "вецер",
          "зямля", "неба", "воблака", "дождж", "снег", "кветка", "трава",
          "ліст", "птушка", "рыба", "конь", "авечка", "карова", "малако",
          "хлеб", "сыр", "яблык", "апельсін", "лімон", "стол", "стул",
          "акно", "дзверы", "падлога", "сцяна", "сад", "рака", "гара",
          "сябар", "праца", "школа", "універсітэт", "горад", "краіна",
          "вуліца", "лес", "поле"}},
        {Hebrew,
         {"שלום", "עולם", "שמש", "ירח", "כוכב", "עץ", "בית", "מכונית",
          "דרך", "ספר", "עט", "מים", "אש", "רוח", "אדמה", "שמיים",
          "ענן", "גשם", "שלג", "פרח", "דשא", "עלה", "ציפור", "דג",
          "סוס", "כבשה", "פרה", "חלב", "לחם", "גבינה", "תפוח", "תפוז",
          "לימון", "שולחן", "כיסא", "חלון", "דלת", "רצפה", "תקרה", "קיר",
          "גן", "נהר", "הר", "חבר", "משפחה", "עבודה", "כיתה", "אוניברסיטה",
          "עיר", "מדינה", "ים"}}};

    srand(time(nullptr));
    QString result;
    int wordCount = 25;
    for (int i = 0; i < wordCount; ++i) {
        QString word = words[keyboardLayout][rand() % words[keyboardLayout].size()];
        if (!result.isEmpty()) {
            result += " ";
        }
        result += word;
    }
    return result;
}

void Text::generateConverter() {
    converter.clear();
    for (int i = 0; i < Keyboard::kLayouts[English].size(); i++) {
        for (int j = 0; j < Keyboard::kLayouts[English][i].size(); j++) {
            converter[Keyboard::kLayouts[English][i][j].toLower()] =
                Keyboard::kLayouts[keyboardLayout][i][j].toLower();
        }
    }
}

void Text::keyPressEvent(QKeyEvent *event) {
    if (event->modifiers() == Qt::ControlModifier) {
        if (event->key() == Qt::Key_R) {
            restart();
        } else if (event->key() == Qt::Key_O) {
            emit openFile();
        }
    } else if (!event->text().isEmpty()) {
        if (text.isEmpty()) {
            emit startTyping();
        }
        if (event->text()[0].isPrint() && text.size() < hint.size()) {
            if (converter.contains(event->text().toLower())) {
                text += event->text()[0].isUpper() && event->text()[0].isLetter()
                            ? converter[event->text().toLower()].toUpper()
                            : converter[event->text().toLower()];
            } else {
                text += event->text();
            }
        } else if (event->text() == "\b") {
            text = text.left(text.size() - 1);
        }
        refresh();
    }
}

void Text::setHint(QString hint) {
    this->hint = hint;
    text = "";
    offset = 0;
    refresh();
    emit reset();
}

void Text::setText(QString text) {
    this->text = text;
}

void Text::setKeyboardLayout(Layout layout) {
    keyboardLayout = layout;
    generateConverter();
    restart();
}

int Text::getTypedWordsCount() {
    return hint.left(text.size()).count(QRegularExpression("[^\\s]+"));
}

void Text::refresh() {
    if (text.size() - offset > kColumnCount * (kRowCount / 2 + 1) &&
        text.size() < hint.size() - kColumnCount) {
        offset += kColumnCount;
    }
    int index = offset;
    for (auto &row : letters) {
        for (Letter *letter : row) {
            letter->reset();
            if (keyboardLayout == Chinese) {
                letter->setFontSize(15);
            }
            if (index < text.size() && index < hint.size()) {
                letter->setLetter(QString(hint[index]));
                if (text[index] == hint[index]) {
                    letter->correct();
                } else {
                    letter->incorrect();
                }
            } else if (index < hint.size()) {
                letter->setLetter(QString(hint[index]));
            }
            index++;
        }
    }
    emit setActive("");
    if (text.size() < hint.size()) {
        letters[(text.size() - offset) / kColumnCount]
               [(text.size() - offset) % kColumnCount]
                   ->next();
        emit setActive(letters[(text.size() - offset) / kColumnCount]
                              [(text.size() - offset) % kColumnCount]
                                  ->text());
    }
    if (text.size() == hint.size()) {
        emit stopTyping();
    }
}

void Text::restart() {
    hint = generate();
    text = "";
    offset = 0;
    refresh();
    emit reset();
}