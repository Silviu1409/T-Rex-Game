#include <SFML/Graphics.hpp>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <string>
#include <list>

using namespace sf;

///functie template - setarea caracteristicilor unui text
template <class T, class U>
void setcaract_text(Text &text, const Font& font, const std::ostringstream& ss, std::string theme, const T font_size = 1, const U x = 0, const U y = 0){
    text.setFont(font);
    text.setString(ss.str());
    text.setCharacterSize(font_size);
    text.setPosition(x, y);
    if (theme == "dark theme"){
        text.setFillColor(Color::White);
    }
    else{
        text.setFillColor(Color::Black);
    }
    text.setStyle(Text::Bold);
}

///clasa template - pozitia in plan a unui element
template <class T>
class point{
    T x;
    T y;
public:
    point(T a=0, T b=0){
        x = a;
        y = b;
    }
    point(const point& p){
        x = p.getx();
        y = p.gety();
    }
    ~point(){
        x = 0;
        y = 0;
    }

    point& operator=(const point& p){
        if(this != &p){
            x = p.getx();
            y = p.gety();
        }
        return *this;
    }

    virtual std::istream& CitireVirtuala(std::istream& input){
        std::cout<<"x = ";
        input>>x;
        std::cout<<"\ny = ";
        input>>y;

        return input;
    }
    virtual std::ostream& AfisareVirtuala(std::ostream& output){
        output<<"x = "<<x<<" / y ="<<y<<".\n";

        return output;
    }

    std::istream& operator>>(std::istream& input){
        return this->CitireVirtuala(input);
    }
    std::ostream& operator<<(std::ostream& output){
        return this->AfisareVirtuala(output);
    }

    void setx(T a){
        x = a;
    }
    void sety(T b){
        y = b;
    }

    T getx() const {
        return x;
    }
    T gety() const {
        return y;
    }
};

///clasa abstracta, nu poate fi instantiata
class AbstractClass{
public:
    virtual void AbstractFunction() = 0;    ///functie pur virtuala
};

///clasa de baza pentru un element de pe ecran
class base : AbstractClass{ ///mostenire private default
    point <float> position;
    Texture *t;
protected:
    Sprite s;
public:
    base(){
        position.setx(0);
        position.sety(0);
        try{
            t = new Texture;
        }
        catch(std::bad_alloc&){ ///exceptie eroare alocare
            exit(EXIT_FAILURE);
        }
        t->create(1, 1);
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(0, 0);
    }
    base(point <float> pozitie, std::string sursa){
        position = pozitie;
        try{
            t = new Texture;
        }
        catch(std::bad_alloc&){ ///exceptie eroare alocare
            exit(EXIT_FAILURE);
        }
        if (!t->loadFromFile(sursa)){
            exit(EXIT_FAILURE);
        }
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    base(std::string sursa, float x=0, float y=0){
        position.setx(x);
        position.sety(y);
        try{
            t = new Texture;
        }
        catch(std::bad_alloc&){ ///exceptie eroare alocare
            exit(EXIT_FAILURE);
        }
        if (!t->loadFromFile(sursa)){
            exit(EXIT_FAILURE);
        }
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    base(point <float> pozitie, Texture textura, float x = 0, float y = 0){
        position = pozitie;
        try{
            t = new Texture(textura);
        }
        catch(std::bad_alloc&){ ///exceptie eroare alocare
            exit(EXIT_FAILURE);
        }
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    base(const base& b){
        position = b.getposition();
        try{
            t = new Texture(*b.gettexture());
        }
        catch(std::bad_alloc&){ ///exceptie eroare alocare
            exit(EXIT_FAILURE);
        }
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    virtual ~base(){
        position.setx(0);
        position.sety(0);
        t=0;
        s.setTexture(*t);
        s.setPosition(0, 0);
        delete t;
    }

    void AbstractFunction(){};  ///suprascriere functie pur virtuala pt a putea instantia obiecte de tip base si derivate

    base& operator=(const base& b){
        if (this != &b){
            position = b.getposition();
            delete t;
            t = new Texture(*b.gettexture());
            t->setSmooth(true);
            s.setTexture(*t);
            s.setPosition(position.getx(), position.gety());
        }
        return *this;
    }

    void setposition(point <float> pozitie){
        position.setx(pozitie.getx());
        position.sety(pozitie.gety());
        s.setPosition(pozitie.getx(), pozitie.gety());
    }
    void setposition(float x = 0, float y = 0){
        position.setx(x);
        position.sety(y);
        s.setPosition(x, y);
    }
    void setpositionx(float x){
        position.setx(x);
        s.setPosition(x, position.gety());
    }
    void setpositiony(float y){
        position.sety(y);
        s.setPosition(position.getx(), y);
    }
    void settexture(Texture texture){
        t->swap(texture);
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    void settexture2(std::string sursa){
        Texture aux;
        if (!aux.loadFromFile(sursa)){
            exit(EXIT_FAILURE);
        }
        t->swap(aux);
        t->setSmooth(true);
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    void setsprite(Sprite sprite){
        s = sprite;
        s.setPosition(position.getx(), position.gety());
    }
    void setsprite(Texture texture){
        s.setTexture(texture);
        s.setPosition(position.getx(), position.gety());
    }

    point <float> getposition() const{
        return position;
    }
    Texture* gettexture() const{
        return t;
    }
    Sprite getsprite() const{
        return s;
    }
};

///clasa pt. setari
class Option{
    Text text;
    bool isOn;
public:
    base *b; ///nested class

    Option(){
        b = new base();
        Font font;
        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            exit(EXIT_FAILURE);
        }
        text.setFont(font);
        text.setCharacterSize(1);
        text.setString("");
        isOn = false;
    }
    Option(point <float> pozitie, std::string sursa, Text x, bool y = false){
        b = new base(pozitie, sursa);
        text = x;
        isOn = y;
    }
    Option(std::string sursa, float x = 0, float y = 0, bool w = false){
        b = new base(sursa, x, y);
        Font font;
        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            exit(EXIT_FAILURE);
        }
        text.setFont(font);
        text.setCharacterSize(1);
        text.setString("");
        isOn = w;
    }
    Option(std::string sursa, Text z, float x = 0, float y = 0, bool w = false){
        b = new base(sursa, x, y);
        text = z;
        isOn = w;
    }
    Option(point <float> pozitie, Texture textura, Text z, float x = 0, float y = 0, bool w = false){
        b = new base(pozitie, textura, x, y);
        text = z;
        isOn = w;
    }
    Option(const Option& o){
        text = o.get_text();
        b = new base(o.get_b());
        isOn = o.get_o();
    }
    ~Option(){
        b = {};
        isOn = false;
        text.setCharacterSize(1);
        text.setString("");
    }

    Option& operator=(const Option& o){
        if(this != &o){
            text = o.get_text();
            delete b;
            b = new base(o.get_b());
            isOn = o.get_o();
        }
        return *this;
    }

    void set_text(Text x){
        text = x;
    }
    void set_o(bool x){
        isOn = x;
    }

    Text get_text() const{
        return text;
    }
    bool get_o() const{
        return isOn;
    }
    base get_b() const{
        return *b;
    }
};

///clasa de baza pt elementele de pe ecran
class Background : public base{
    float speed;
public:
    Background() : base(){
        speed = 0;
    }
    Background(point <float> pozitie, std::string sursa, float v) : base(pozitie, sursa){
        speed = v;
    }
    Background(std::string sursa, float v, float x = 0, float y = 0) : base(sursa, x, y){
        speed = v;
    }
    Background(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0) : base(pozitie, textura, x, y){
        speed = v;
    }
    Background(const Background& b) : base(b){
        speed = b.getspeed();
    }
    virtual ~Background(){
        speed = 0;
    }

    Background& operator= (const Background& b){
        if (this != &b){
            this->setposition(b.getposition());
            this->settexture(*b.gettexture());
            speed = b.getspeed();
        }
        return *this;
    }

    virtual void Move(){
        this->setpositionx(this->getposition().getx() + this->getspeed());
    }

    void setspeed(float v){
        speed = v;
    }

    float getspeed() const{
        return speed;
    }
};

///clase derivate
class Cactus:virtual public Background{
public:
    Cactus():Background(){};
    Cactus(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Cactus(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Cactus(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
    Cactus(const Cactus& aux) : Background(aux){};
    ~Cactus(){};

    Cactus& operator=(const Cactus& aux){
        if (this != &aux){
            this->setposition(aux.getposition());
            this->settexture(*aux.gettexture());
            this->setspeed(aux.getspeed());
        }
        return *this;
    }
};

class Stars:virtual public Background{
public:
    Stars():Background(){};
    Stars(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Stars(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Stars(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
    Stars(const Stars& aux) : Background(aux){};
    ~Stars(){};

    Stars& operator=(const Stars& aux){
        if (this != &aux){
            this->setposition(aux.getposition());
            this->settexture(*aux.gettexture());
            this->setspeed(aux.getspeed());
        }
        return *this;
    }
};

///singleton
class Bolt:public Background{
    bool isOn;
    static Bolt *object;
    Bolt():Background(){
        isOn = false;
    }
    Bolt(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){
        isOn = false;
    };
    Bolt(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){
        isOn = false;
    };
    Bolt(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){
        isOn = false;
    };
public:
    static Bolt* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Bolt(sursa, v, x, y);
        return object;
    }
    ~Bolt(){
        isOn = false;
        object = 0;
    };

    void set_o(bool x){
        isOn = x;
    }
    bool get_o() const{
        return isOn;
    }
};
Bolt* Bolt::object=0;

///singleton, desi are tot un bool ca membru, nu il pot mosteni din clasa Bolt, deoarece nu se poate apela constructorul din clasa Bolt, deoarece este private
class Button:public Background{
    bool isPaused;
    static Button *object;
    Button():Background(){
        isPaused = false;
    };
    Button(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){
        isPaused = false;
    };
    Button(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){
        isPaused = false;
    };
    Button(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){
        isPaused = false;
    };
public:
    static Button* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Button(sursa, v, x, y);
        return object;
    }
    ~Button(){
        isPaused = false;
        object = 0;
    };

    void setp(bool x){
        isPaused = x;
    }
    bool getp() const{
        return isPaused;
    }
};
Button* Button::object=0;

///singleton
class Moon:public Background{
    static Moon *object;
    Moon():Background(){};
    Moon(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Moon(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Moon(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
public:
    static Moon* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Moon(sursa, v, x, y);
        return object;
    }
    ~Moon(){
        object = 0;
    }
};
Moon* Moon::object=0;

///singleton
class Bird:public Background{
    static Bird *object;
    Bird():Background(){};
    Bird(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Bird(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Bird(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
public:
    static Bird* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Bird(sursa, v, x, y);
        return object;
    }

    ~Bird(){
        object = 0;
    }
};
Bird* Bird::object=0;

///doubleton
class Cloud:public Background{
    static Cloud *object1;
    static Cloud *object2;
    Cloud():Background(){};
    Cloud(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Cloud(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Cloud(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
public:
    static Cloud* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object1){
            object1=new Cloud(sursa, v, x, y);
            return object1;
        }
        else if(!object2){
                object2=new Cloud(sursa, v, x, y);
                return object2;
            }
        return object1;
    }

    ~Cloud(){
        if(object2) object2 = 0;
        else object1=0;
    }
};
Cloud* Cloud::object1=0;
Cloud* Cloud::object2=0;

///singleton
class Dino: public Cactus,
            public Stars{
    static Dino *object;
    Dino():Background(){
        isJumping = false;
        isDown = false;
    }
    Dino(point <float> pozitie, std::string sursa, float v):Background(pozitie, sursa, v){
        isJumping = false;
        isDown = false;
    }
    Dino(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){
        isJumping = false;
        isDown = false;
    }
    Dino(point <float> pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){
        isJumping = false;
        isDown = false;
    }
    bool isJumping;
    bool isDown;
public:
    static Dino* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Dino(sursa, v, x, y);
        return object;
    }

    ~Dino(){
        isJumping = false;
        isDown = false;
        object = 0;
    }

    void Move(){
        this->setpositiony(this->getposition().gety() + this->getspeed());
    }

    void setj(bool x){
        isJumping = x;
    }
    void setd(bool x){
        isDown = x;
    }

    bool getj() const{
        return isJumping;
    }
    bool getd() const{
        return isDown;
    }
};
Dino* Dino::object=0;

///functie pt schimbare viteze fizici
void setspeeds(std::list <float> &a, Background &b, Background &c, Moon &d, Bird &e, Cloud &f, Cloud &g, std::vector <Stars> &h, std::vector <Cactus> &i){
    a.push_back(b.getspeed());
    b.setspeed(b.getspeed() / 4);
    a.push_back(c.getspeed());
    c.setspeed(c.getspeed() / 4);
    a.push_back(d.getspeed());
    d.setspeed(d.getspeed() / 4);
    a.push_back(e.getspeed());
    e.setspeed(e.getspeed() / 4);
    a.push_back(f.getspeed());
    f.setspeed(f.getspeed() / 4);
    a.push_back(g.getspeed());
    g.setspeed(g.getspeed() / 4);
    std::for_each(h.begin(), h.end(), [&](Stars &j){
        a.push_back(j.getspeed());
        j.setspeed(j.getspeed() / 4);
    });
    std::for_each(i.begin(), i.end(), [&](Cactus &j){
        a.push_back(j.getspeed());
        j.setspeed(j.getspeed() / 4);
    });
}

///functie pt revenire la viteze initiale
void getspeeds(std::list <float> a, Background &b, Background &c, Moon &d, Bird &e, Cloud &f, Cloud &g, std::vector <Stars> &h, std::vector <Cactus> &i){
    std::list <float>::iterator it = a.begin();
    b.setspeed(*it);
    ++it;
    c.setspeed(*it);
    ++it;
    d.setspeed(*it);
    ++it;
    e.setspeed(*it);
    ++it;
    f.setspeed(*it);
    ++it;
    g.setspeed(*it);
    ++it;
    for(int j=6; j<6 + abs(h.size()); j++){
        h[j-6].setspeed(*it);
        ++it;
    }
    for(int j = 6 + abs(h.size()); j<6 + abs(h.size() + i.size()); j++){
        i[j-6-h.size()].setspeed(*it);
        ++it;
    }
}

///clasa aplicatie, singleton
class App{
    static App *object;
   	App(int width=0, int height=0, std::string titlu="Title", int fps=0, bool keyspam=false, bool icon=false, std::string adresa_icon=".png"){
        window = new RenderWindow;
        window->create(VideoMode(width, height), titlu);
        window->setFramerateLimit(fps);
        window->setKeyRepeatEnabled(keyspam);
        if (icon){
            Image icon;
            if(icon.loadFromFile(adresa_icon))
                window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
            else{
                exit(EXIT_FAILURE);
            }
        }
        highscore = 0;
        score = 0;
        isCheatActivated = false;
        frames = fps;
        showfps = false;
        theme = "dark theme";
        showTips = false;
        speedMultiplier = 1;
        isShooting = false;
    }
   	RenderWindow* window;
   	float score;
   	int highscore;
   	bool isCheatActivated;
   	int frames;
   	bool showfps;
   	std::string theme;
   	bool showTips;
   	float speedMultiplier;
   	bool isShooting;
public:
    static App* getInstance(int width, int height, std::string titlu, int fps, bool keyspam, bool icon, std::string adresa_icon){
		if(!object)
            object=new App(width, height, titlu, fps, keyspam, icon, adresa_icon);
        return object;
    }

    ~App(){
        delete window;
        score = 0;
        highscore = 0;
        isCheatActivated = false;
        frames = 0;
        showfps = false;
        theme.clear();
        showTips = false;
        speedMultiplier = 0;
        isShooting = false;
    }

    bool Homescreen(){
        ///verificare setari
        std::ifstream f("config.txt");
        std::string config;
        getline(f, config);
        getline(f, config);

        if (config == ""){
            config = "100011";
        }
        else{
            ///parcurgere string cu iterator de tip char
            for(std::string::iterator i = config.begin(); i<config.end(); i++){
                *i -= 81;
            }
        }

        if (config[0] == 49){
            frames = 30;
        }
        else if (config[0] == 50){
            frames = 60;

        }
        else{
            frames = 120;
        }
        window->setFramerateLimit(frames);

        if (config[1] == 48){
            window->setVerticalSyncEnabled(false);
        }
        else{
            window->setVerticalSyncEnabled(true);
        }

        if (config[2] == 48){
            showfps = false;
        }
        else{
            showfps = true;
        }

        if (config[3] == 48){
            showTips = false;
        }
        else{
            showTips = true;
        }

        if (config[4] == 49){
            speedMultiplier = 1;
        }
        else if(config[4] == 50){
            speedMultiplier = 1.25;
        }
        else{
            speedMultiplier = 1.5;
        }

        if (config[5] == 49){
            theme = "dark theme";
        }
        else{
            theme = "light theme";
        }

        f.close();

        ///smart pointer, se va distruge automat cand nu va mai fi apelat sau la finalul functiei, pt a nu avea memory leaks
        ///auto - tipul de date va fi luat automat, make_unique creeaza un smart pointer folosind constructor si il atribuie variabilei
        auto background = std::make_unique <Background> ("textures/" + theme + "/background homescreen.png", 0);

        Dino *dino = dino->getInstance("textures/" + theme + "/dino start.png", 0, 50, 305);
        Button *button = button->getInstance("textures/" + theme + "/settings.png", 0, 520, 25);

        Text text;
        Font font;
        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            window->close();
            return false;
        }

        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Press\tSPACE\tor\tLEFT\tCLICK\tto\tbegin"), theme, 40, 150, 100);

        float pos = 0.f;
        bool img = false;

        while(window->isOpen()){
            Event event;
            while (window->pollEvent(event)){
                switch(event.type){
                    case Event::Closed:
                        return false;
                    case Event::KeyReleased:
                        if (event.key.code == Keyboard::Space){
                            window->clear();

                            window->draw(background->getsprite());
                            dino->settexture2("textures/" + theme + "/dino static.png");
                            window->draw(dino->getsprite());

                            window->display();

                            float v = -60.0/frames;

                            while(dino->getposition().gety()<=305){
                                window->clear();

                                window->draw(background->getsprite());
                                dino->setspeed(dino->getspeed() + v*60.0/frames);
                                dino->Move();
                                window->draw(dino->getsprite());

                                window->display();
                                if (dino->getposition().gety()<=225){
                                    v = 60.0/frames;
                                }
                            }
                            delete button;

                            Sleep(0.001);

                            return true;
                        }
                        else if (event.key.code == Keyboard::Tilde){
                            if (isCheatActivated){
                                isCheatActivated = false;
                            }
                            else{
                                isCheatActivated = true;
                            }
                        }
                    case Event::MouseButtonReleased:
                        if (event.mouseButton.button == Mouse::Left){
                            Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));
                            FloatRect bound = button->getsprite().getGlobalBounds();
                            if (!bound.contains(mouse)){
                                window->clear();

                                window->draw(background->getsprite());
                                dino->settexture2("textures/" + theme + "/dino static.png");
                                window->draw(dino->getsprite());

                                window->display();

                                float v = -60.0/frames;

                                while(dino->getposition().gety()<=305){
                                    window->clear();

                                    window->draw(background->getsprite());
                                    dino->setspeed(dino->getspeed() + v*60.0/frames);
                                    dino->Move();
                                    window->draw(dino->getsprite());

                                    window->display();

                                    if (dino->getposition().gety()<=225){
                                        v = 60.0/frames;
                                    }
                                }

                                Sleep(0.001);

                                return true;
                            }
                            else{
                                delete button;  ///stergere instanta(singleton, pentru a crea o noua instanta pt buton in meniul de setari)

                                window->clear();

                                window->draw(background->getsprite());
                                window->draw(dino->getsprite());
                                window->draw(text);

                                window->display();

                                window->setActive(false);
                                window->setVisible(false);

                                Settings();

                                window->setVisible(true);
                                window->setActive(true);

                                background->settexture2("textures/" + theme + "/background homescreen.png");
                                dino->settexture2("textures/" + theme + "/dino start.png");
                                button = button->getInstance("textures/" + theme + "/settings.png", 0, 520, 25);    ///refac instanta de dinainte
                                setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Press\tSPACE\tor\tLEFT\tCLICK\tto\tbegin"), theme, 40, 150, 100);
                            }
                        }
                    default:{}
                }
            }

            if (pos>=10){
                img = true;
                dino->settexture2("textures/" + theme + "/dino start 1.png");
            }
            else if(pos<=0){
                img = false;
                dino->settexture2("textures/" + theme + "/dino start 2.png");
            }
            if (img){
                pos -= 60.0/frames;
            }
            else pos += 60.0/frames;

            window->clear();

            window->draw(background->getsprite());
            window->draw(dino->getsprite());
            window->draw(text);
            window->draw(button->getsprite());

            window->display();

            Sleep(0.001);
        }
        return false;
    }

    void Settings(){
        std::unique_ptr <RenderWindow> setari(new RenderWindow);

        setari->create(VideoMode(810, 375), "", Style::None);
        setari->setFramerateLimit(frames);
        setari->setKeyRepeatEnabled(false);

        std::unique_ptr <Background> background(new Background("textures/" + theme + "/background settings.png", 0) );
        Button *button = button->getInstance("textures/" + theme + "/close.png", 0, 770, 0);

        ///FrameCap, Graphics, Gameplay, Difficulty, Theme;
        std::list <Text> settings_names;
        std::vector <Option> settings_options;

        Text text;
        Font font;
        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            setari->close();
            exit(EXIT_FAILURE);
        }

        ///30/60/120
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Framecap"), theme, 25, 145, 100);
        settings_names.push_back(text);
        ///v-sync, show fps
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Graphics"), theme, 25, 145, 190);
        settings_names.push_back(text);
        ///show tips
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Gameplay"), theme, 25, 145, 280);
        settings_names.push_back(text);
        ///easy/medium/hard
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Difficulty"), theme, 25, 525, 100);
        settings_names.push_back(text);
        ///dark theme/light theme
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Theme"), theme, 25, 560, 190);
        settings_names.push_back(text);

        std::ifstream f("config.txt");
        std::string scores, config;
        getline(f, scores);
        getline(f, config);

        if (config == ""){
            config = "100011";
        }
        else{
            ///parcurgere string cu lambda funtion
            std::for_each(config.begin(), config.end(), [](char &i){
                i -= 81;
            });
        }

        Option aux("textures/" + theme + "/unchecked box.png", 50, 150);
        FloatRect tmp = aux.b->getsprite().getGlobalBounds();

        ///setare optiuni
        for(int i=0; i<3; i++){
            settings_options.push_back(aux);
            aux.b->setposition(aux.b->getposition().getx() + 100, aux.b->getposition().gety());
        }

        aux.b->setposition(100, 240);

        for(int i=0; i<2; i++){
            settings_options.push_back(aux);
            aux.b->setposition(aux.b->getposition().getx() + 100, aux.b->getposition().gety());
        }

        aux.b->setposition(150, 330);

        settings_options.push_back(aux);

        aux.b->setposition(500, 150);

        for(int i=0; i<3; i++){
            settings_options.push_back(aux);
            aux.b->setposition(aux.b->getposition().getx() + 100, aux.b->getposition().gety());
        }

        aux.b->setposition(550, 240);

        for(int i=0; i<2; i++){
            settings_options.push_back(aux);
            aux.b->setposition(aux.b->getposition().getx() + 100, aux.b->getposition().gety());
        }

        int tmpnr;

        tmpnr = config[0] - 48;
        settings_options[tmpnr - 1].b->settexture2("textures/" + theme + "/checked box.png");
        settings_options[tmpnr - 1].set_o(true);

        for(int i=1; i<4; i++){
            tmpnr = config[i] - 48;
            if (tmpnr){
                settings_options[i + 2].b->settexture2("textures/" + theme + "/checked box.png");
                settings_options[i + 2].set_o(true);
            }
        }

        tmpnr = config[4] - 48;
        settings_options[5 + tmpnr].b->settexture2("textures/" + theme + "/checked box.png");
        settings_options[5 + tmpnr].set_o(true);

        tmpnr = config[5] - 48;
        settings_options[8 + tmpnr].b->settexture2("textures/" + theme + "/checked box.png");
        settings_options[8 + tmpnr].set_o(true);

        int i = 0;

        ///setare nume optiuni
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("30\tfps"), theme, 17, 72, 146);
        settings_options[i].set_text(text);
        i++;
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("60\tfps"), theme, 17, 172, 146);
        settings_options[i].set_text(text);
        i++;
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("120\tfps"), theme, 17, 272, 146);
        settings_options[i].set_text(text);
        i++;

        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("V\tSync"), theme, 17, 122, 236);
        settings_options[i].set_text(text);
        i++;
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Show\tFPS"), theme, 17, 222, 236);
        settings_options[i].set_text(text);
        i++;

        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Show\tTips"), theme, 17, 172, 326);
        settings_options[i].set_text(text);
        i++;

        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Easy"), theme, 17, 522, 146);
        settings_options[i].set_text(text);
        i++;
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Medium"), theme, 17, 622, 146);
        settings_options[i].set_text(text);
        i++;
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Hard"), theme, 17, 722, 146);
        settings_options[i].set_text(text);
        i++;

        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Dark"), theme, 17, 572, 236);
        settings_options[i].set_text(text);
        i++;
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Light"), theme, 17, 672, 236);
        settings_options[i].set_text(text);

        ///titlu meniu setari
        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Settings"), theme, 40, 310, 10);

        while(setari->isOpen()){
            Event event;

            while (setari->pollEvent(event)){
                switch(event.type){
                    case Event::MouseButtonReleased:
                        if (event.mouseButton.button == Mouse::Left){
                            Vector2f mouse = setari->mapPixelToCoords(Mouse::getPosition(*setari));
                            FloatRect bound = button->getsprite().getGlobalBounds();

                            if (bound.contains(mouse)){ ///este butonul de exit
                                delete button;  ///sterg instanta butonului pt o alta instanta in meniul de homescreen/deathscreen

                                Sleep(100);

                                std::ofstream g("config.txt");

                                std::for_each(config.begin(), config.end(), [](char &i){
                                    i += 81;
                                });

                                g<<scores<<"\n";
                                g<<config;

                                g.close();

                                return;
                            }
                            else{
                                FloatRect* bound_buttons = new FloatRect[11];   ///alocare dinamica de variabile
                                for (int i=0; i<11; i++){
                                    bound_buttons[i] = settings_options[i].b->getsprite().getGlobalBounds();
                                }

                                if (tmp.contains(mouse)){
                                    if (!settings_options[0].get_o()){
                                        settings_options[0].set_o(true);
                                        settings_options[1].set_o(false);
                                        settings_options[2].set_o(false);
                                        settings_options[0].b->settexture2("textures/" + theme + "/checked box.png");
                                        settings_options[1].b->settexture2("textures/" + theme + "/unchecked box.png");
                                        settings_options[2].b->settexture2("textures/" + theme + "/unchecked box.png");
                                        frames = 30;
                                        setari->setFramerateLimit(frames);
                                        window->setFramerateLimit(frames);
                                        config[0] = '1';
                                    }
                                }
                                else if (bound_buttons[1].contains(mouse)){
                                        if (!settings_options[1].get_o()){
                                            settings_options[0].set_o(false);
                                            settings_options[1].set_o(true);
                                            settings_options[2].set_o(false);
                                            settings_options[0].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            settings_options[1].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[2].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            frames = 60;
                                            setari->setFramerateLimit(frames);
                                            window->setFramerateLimit(frames);
                                            config[0] = '2';
                                        }
                                }
                                else if (bound_buttons[2].contains(mouse)){
                                        if (!settings_options[2].get_o()){
                                            settings_options[0].set_o(false);
                                            settings_options[1].set_o(false);
                                            settings_options[2].set_o(true);
                                            settings_options[0].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            settings_options[1].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            settings_options[2].b->settexture2("textures/" + theme + "/checked box.png");
                                            frames = 120;
                                            setari->setFramerateLimit(frames);
                                            window->setFramerateLimit(frames);
                                            config[0] = '3';
                                        }
                                }
                                else if (bound_buttons[3].contains(mouse)){
                                        if (!settings_options[3].get_o()){
                                            settings_options[3].set_o(true);
                                            settings_options[3].b->settexture2("textures/" + theme + "/checked box.png");
                                            setari->setVerticalSyncEnabled(true);
                                            window->setVerticalSyncEnabled(true);
                                            config[1] = '1';
                                        }
                                        else{
                                            settings_options[3].set_o(false);
                                            settings_options[3].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            setari->setVerticalSyncEnabled(false);
                                            window->setVerticalSyncEnabled(false);
                                            config[1] = '0';
                                        }
                                }
                                else if (bound_buttons[4].contains(mouse)){
                                        if (!settings_options[4].get_o()){
                                            settings_options[4].set_o(true);
                                            settings_options[4].b->settexture2("textures/" + theme + "/checked box.png");
                                            showfps = true;
                                            config[2] = '1';
                                        }
                                        else{
                                            settings_options[4].set_o(false);
                                            settings_options[4].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            showfps = false;
                                            config[2] = '0';
                                        }
                                }
                                else if (bound_buttons[5].contains(mouse)){
                                        if (!settings_options[5].get_o()){
                                            settings_options[5].set_o(true);
                                            settings_options[5].b->settexture2("textures/" + theme + "/checked box.png");
                                            showTips = true;
                                            config[3] = '1';
                                        }
                                        else{
                                            settings_options[5].set_o(false);
                                            settings_options[5].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            showTips = false;
                                            config[3] = '0';
                                        }
                                }
                                else if (bound_buttons[6].contains(mouse)){
                                        if (!settings_options[6].get_o()){
                                            settings_options[6].set_o(true);
                                            settings_options[7].set_o(false);
                                            settings_options[8].set_o(false);
                                            settings_options[6].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[7].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            settings_options[8].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            speedMultiplier = 1;
                                            config[4] = '1';
                                        }
                                }
                                else if (bound_buttons[7].contains(mouse)){
                                        if (!settings_options[7].get_o()){
                                            settings_options[7].set_o(true);
                                            settings_options[6].set_o(false);
                                            settings_options[8].set_o(false);
                                            settings_options[7].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[6].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            settings_options[8].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            speedMultiplier = 1.25;
                                            config[4] = '2';
                                        }
                                }
                                else if (bound_buttons[8].contains(mouse)){
                                        if (!settings_options[8].get_o()){
                                            settings_options[8].set_o(true);
                                            settings_options[6].set_o(false);
                                            settings_options[7].set_o(false);
                                            settings_options[8].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[6].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            settings_options[7].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            speedMultiplier = 1.5;
                                            config[4] = '3';
                                        }
                                }
                                else if (bound_buttons[9].contains(mouse)){

                                            settings_options[9].set_o(true);
                                            settings_options[10].set_o(false);
                                            settings_options[9].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[10].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            theme = "dark theme";
                                            config[5] = '1';

                                            background->settexture2("textures/" + theme + "/background settings.png");
                                            button->settexture2("textures/" + theme + "/close.png");
                                            text.setFillColor(Color::White);

                                            for(std::list<Text>::iterator it = settings_names.begin(); it != settings_names.end(); ++it){
                                                (*it).setFillColor(Color::White);
                                            }

                                            std::for_each(settings_options.begin(), settings_options.end(), [&](Option &i){
                                                Text tmp = i.get_text();
                                                tmp.setFillColor(Color::White);
                                                i.set_text(tmp);
                                                i.b->settexture2("textures/" + theme + "/unchecked box.png");
                                            });

                                            settings_options[config[0] - 49].b->settexture2("textures/" + theme + "/checked box.png");
                                            for(int i=1; i<4; i++){
                                                if (config[i] == 49){
                                                    settings_options[i + 2].b->settexture2("textures/" + theme + "/checked box.png");
                                                }
                                            }
                                            settings_options[config[4] - 43].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[config[5] - 40].b->settexture2("textures/" + theme + "/checked box.png");
                                }
                                else if (bound_buttons[10].contains(mouse)){

                                            settings_options[10].set_o(true);
                                            settings_options[9].set_o(false);
                                            settings_options[10].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[9].b->settexture2("textures/" + theme + "/unchecked box.png");
                                            theme = "light theme";
                                            config[5] = '2';

                                            background->settexture2("textures/" + theme + "/background settings.png");
                                            button->settexture2("textures/" + theme + "/close.png");
                                            text.setFillColor(Color::Black);
                                            for(std::list<Text>::iterator it = settings_names.begin(); it != settings_names.end(); ++it){
                                                (*it).setFillColor(Color::Black);
                                            }

                                            std::for_each(settings_options.begin(), settings_options.end(), [&](Option &i){
                                                Text tmp = i.get_text();
                                                tmp.setFillColor(Color::Black);
                                                i.set_text(tmp);
                                                i.b->settexture2("textures/" + theme + "/unchecked box.png");
                                            });

                                            settings_options[config[0] - 49].b->settexture2("textures/" + theme + "/checked box.png");
                                            for(int i=1; i<4; i++){
                                                if (config[i] == 49){
                                                    settings_options[i + 2].b->settexture2("textures/" + theme + "/checked box.png");
                                                }
                                            }
                                            settings_options[config[4] - 43].b->settexture2("textures/" + theme + "/checked box.png");
                                            settings_options[config[5] - 40].b->settexture2("textures/" + theme + "/checked box.png");
                                }
                                delete[] bound_buttons; ///sterg elementele alocate dinamic pt. a preveni memory leaks
                            }
                        }
                        break;
                    default:{}
                }
            }
            setari->clear();

            setari->draw(background->getsprite());
            setari->draw(button->getsprite());
            setari->draw(text);

            for(std::list<Text>::iterator it = settings_names.begin(); it != settings_names.end(); ++it){
                setari->draw(*it);
            }

            std::for_each(settings_options.begin(), settings_options.end(), [&](Option &i){
                setari->draw(i.get_b().getsprite());
                setari->draw(i.get_text());
            });

            setari->display();

            Sleep(0.001);
        }
    }

    bool Game(){
        window->clear();

        window->setFramerateLimit(frames);

        srand(time(0));

        ///get highscore from file
        std::ifstream f("config.txt");
        std::string aux;
        getline(f, aux);
        if (aux != ""){
            for(int i=0; i<abs(aux.length()); i++)
                aux[i] -= 81;
            std::stringstream tmp(aux);
            tmp>>highscore;
        }

        Background background("textures/" + theme + "/background.png", -420.0/frames * speedMultiplier), pre_background("textures/" + theme + "/background.png", -420.0/frames * speedMultiplier, 2400);
        Dino *dino = dino->getInstance("textures/" + theme + "/dino static.png", 0, 50, 305);
        Moon *moon = moon->getInstance("textures/dark theme/moon.png", -60.0/frames * speedMultiplier, 1080+rand()%500, 5+rand()%50);

        std::string x;
        std::vector <Stars> stars;
        if (theme == "dark theme"){
            for (int i=0; i<3; i++){
                x = "textures/" + theme + "/star " + std::to_string(i+1) + ".png";
                Stars tmp(x, -60.0/frames * speedMultiplier, i*300 + rand()%180, 25+rand()%150);
                stars.push_back(tmp);
                tmp.setposition(i*300 + rand()%180, 25+rand()%150);
                stars.push_back(tmp);
                tmp.setposition(i*300 + rand()%180, 25+rand()%150);
                stars.push_back(tmp);
            }
        }

        Bird *bird = bird->getInstance("textures/" + theme + "/bird 1.png", -300.0/frames * speedMultiplier, 3240+rand()%1080, 62+rand()%238);
        Cloud *cloud1 = cloud1->getInstance("textures/" + theme + "/cloud.png", -75.0/frames * speedMultiplier, 1080+rand()%540, 25+rand()%125);
        Cloud *cloud2 = cloud2->getInstance("textures/" + theme + "/cloud.png", -75.0/frames * speedMultiplier, 1620+rand()%540, 25+rand()%125);

        std::vector <Cactus> cactus;
        for (int i=0; i<14; i++){
            x = "textures/" + theme + "/cactus " + std::to_string(i+1) + ".png";
            Cactus tmp(x, -420.0/frames * speedMultiplier, 2081, 501);
            cactus.push_back(tmp);
        }

        set_score(0);

        Text text, text_hi, text_fps;
        Font font;
        std::ostringstream scor, high_scor, fps;

        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            std::cout<<"Error loading file!"<<std::endl;
            window->close();
            exit(EXIT_FAILURE);
            return false;
        }

        scor<<score;
        high_scor<<"HI\t"<<highscore;
        setcaract_text <int, float> (text, font, scor, theme, 30, 1060, 0);

        int tmp = highscore, p=0;

        while (tmp>9){
            tmp /= 10;
            p++;
        }

        setcaract_text <int, float> (text_hi, font, high_scor, theme, 30, 1000 - 17*p, 30);

        scor.str("");

        float pos = 0.0, v = -60.0/frames * speedMultiplier, renderDistance = 1080.0;
        bool img = false;
        int nr = 10, width = 1060, difchg = 1000;
        std::vector <int> poz = {0,0,0,0,0,0,0,0};

        Button *button = button->getInstance("textures/" + theme + "/pause.png", 0, 520, 25);
        Bolt *bolt = bolt->getInstance("textures/" + theme + "/bolt.png", 600.0/frames, -500, -250);

        std::unique_ptr <bool[]> tipsShown(new bool[4]{0, 0, 0, 0});
        std::list <float> prev_speed;
        std::vector <Text> tips;

        Text tip;
        setcaract_text <int, float> (tip, font, static_cast <std::ostringstream>("Press SPACE or LEFT CLICK to JUMP"), theme, 18, 50, 75);
        tips.push_back(tip);
        setcaract_text <int, float> (tip, font, static_cast <std::ostringstream>("Press DOWN ARROW or RIGHT CLICK to CROUCH"), theme, 18, 50, 75);
        tips.push_back(tip);
        setcaract_text <int, float> (tip, font, static_cast <std::ostringstream>("Press X or MIDDLE CLICK to SHOOT BOLTS"), theme, 18, 50, 125);
        tips.push_back(tip);

        int slowdown = 4;

        Clock clock;    ///counter pt timp
        float dt;   ///time between loops

        while (window->isOpen())
        {
            dt = 0.f;

            Event event;
            while (window->pollEvent(event)){
                switch(event.type){
                    case Event::Closed:
                        return false;
                    case Event::KeyPressed:
                        if (event.key.code == Keyboard::Space){
                            if (!dino->getj()){
                                dino->setj(true);
                                dino->setpositiony(dino->getposition().gety()+v);
                                dino->settexture2("textures/" + theme + "/dino static.png");
                                if (tipsShown[2]){
                                    tipsShown[2] = false;
                                    getspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                    slowdown = 4;
                                }
                            }
                        }
                        else if (event.key.code == Keyboard::Down){
                            dino->setd(true);
                            window->setKeyRepeatEnabled(true);
                            if (tipsShown[3]){
                                tipsShown[3] = false;
                                getspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                slowdown = 4;
                            }
                        }
                        else if (event.key.code == Keyboard::Tilde){
                            if (isCheatActivated){
                                isCheatActivated = false;
                            }
                            else{
                                isCheatActivated = true;
                            }
                        }
                        else if (event.key.code == Keyboard::X){
                                if (!dino->getd() && !bolt->get_o()){
                                    bolt->set_o(true);
                                    bolt->setposition(130, dino->getposition().gety() + 10);
                                    if (tipsShown[3]){
                                        tipsShown[3] = false;
                                        getspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                        slowdown = 4;
                                    }
                                }
                        }
                        else if (event.key.code == Keyboard::P){
                                if (!button->getp()){
                                    button->settexture2("textures/" + theme + "/resume.png");
                                    button->setp(true);

                                    std::ostringstream aux;
                                    aux<<"PAUSED";

                                    Text tmp;
                                    setcaract_text <int, float> (tmp, font, aux, theme, 40, 468, 75);
                                    tmp.setStyle(Text::Italic);

                                    window->draw(tmp);
                                    window->draw(button->getsprite());

                                    window->display();

                                    window->setFramerateLimit(1);
                                }
                                else{
                                    button->settexture2("textures/" + theme + "/pause.png");
                                    button->setp(false);

                                    window->setFramerateLimit(frames);
                                }
                        }
                        break;
                    case Event::MouseButtonPressed:
                        if (event.mouseButton.button == Mouse::Left){
                            Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));
                            FloatRect bound = button->getsprite().getGlobalBounds();
                            if (!dino->getj() && !bound.contains(mouse)){
                                dino->setj(true);
                                dino->setpositiony(dino->getposition().gety()+v);
                                dino->settexture2("textures/" + theme + "/dino static.png");
                                if (tipsShown[2]){
                                    tipsShown[2] = false;
                                    getspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                    slowdown = 4;
                                }
                            }
                            else if (bound.contains(mouse)){
                                if (!button->getp()){
                                    button->settexture2("textures/" + theme + "/resume.png");
                                    button->setp(true);

                                    std::ostringstream aux;
                                    aux<<"PAUSED";

                                    Text tmp;
                                    setcaract_text <int, float> (tmp, font, aux, theme, 40, 468, 75);
                                    tmp.setStyle(Text::Italic);

                                    window->draw(tmp);
                                    window->draw(button->getsprite());

                                    window->display();

                                    window->setFramerateLimit(1);
                                }
                                else{
                                    button->settexture2("textures/" + theme + "/pause.png");
                                    button->setp(false);

                                    window->setFramerateLimit(frames);
                                }
                            }
                        }
                        else if (event.mouseButton.button == Mouse::Right){
                            dino->setd(true);
                            window->setKeyRepeatEnabled(true);
                            if (tipsShown[3]){
                                tipsShown[3] = false;
                                getspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                slowdown = 4;
                            }
                        }
                        else if (event.mouseButton.button == Mouse::Middle){
                                if (!dino->getd() && !bolt->get_o()){
                                    bolt->set_o(true);
                                    bolt->setposition(130, dino->getposition().gety() + 10);
                                    if (tipsShown[3]){
                                        tipsShown[3] = false;
                                        getspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                        slowdown = 4;
                                    }
                                }
                        }
                        break;
                    case Event::KeyReleased:
                        if (event.key.code == Keyboard::Down){
                            dino->setd(false);
                            window->setKeyRepeatEnabled(false);
                        }
                        break;
                    case Event::MouseButtonReleased:
                        if (event.mouseButton.button == Mouse::Right){
                            dino->setd(false);
                            window->setKeyRepeatEnabled(false);
                        }
                        break;
                    default:{}
                }
            }

            if (!button->getp()){
                if (background.getposition().getx() < -2400){
                    background.setpositionx(2400);
                }
                else if (pre_background.getposition().getx() < -2400){
                    pre_background.setpositionx(2400);
                }

                if (theme == "dark theme"){
                    if (moon->getposition().getx() < -30){
                        moon->setposition(1280+rand()%500, 5+rand()%50);
                    }
                }

                if (bird->getposition().getx() < -70){
                    bird->setposition(2160+rand()%1080, 62+rand()%238);
                }

                if (cloud1->getposition().getx() < -63){
                    cloud1->setposition(1080+rand()%540, 25+rand()%125);
                }
                if (cloud2->getposition().getx() < -63){
                    cloud2->setposition(1620+rand()%540, 25+rand()%125);
                }

                if (score>difchg){
                    difchg+=1000;

                    background.setspeed(background.getspeed()*1.1);
                    pre_background.setspeed(pre_background.getspeed()*1.1);
                    if (theme == "dark theme"){
                        moon->setspeed(moon->getspeed()*1.1);
                    }
                    cloud1->setspeed(cloud1->getspeed()*1.1);
                    cloud2->setspeed(cloud2->getspeed()*1.1);
                    bird->setspeed(bird->getspeed()*1.1);
                    for (int i=0; i<14; i++){
                        cactus[i].setspeed(cactus[i].getspeed()*1.1);
                    }
                }

                if (showTips){
                    if (!tipsShown[0]){
                        for(int i=0; i<abs(cactus.size()); i++){
                            if(400 > cactus[i].getposition().getx() && 150 < cactus[i].getposition().getx()){
                                tipsShown[0] = true;
                                tipsShown[2] = true;
                                setspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                                slowdown = 1;
                                break;
                            }
                        }
                    }
                    else if(!tipsShown[1]){
                        if(550 > bird->getposition().getx() && 150 < bird->getposition().getx()){
                            tipsShown[1] = true;
                            tipsShown[3] = true;
                            setspeeds(prev_speed, background, pre_background, *moon, *bird, *cloud1, *cloud2, stars, cactus);
                            slowdown = 1;
                        }
                    }
                }

                background.Move();
                pre_background.Move();
                if (theme == "dark theme"){
                    moon->Move();
                }
                bird->Move();
                cloud1->Move();
                cloud2->Move();

                renderDistance += background.getspeed();

                if (renderDistance < 0){
                    renderDistance = 1080*9;
                    poz = {rand()%4, rand()%4, 4+rand()%2, 6+rand()%6, 6+rand()%6, 6+rand()%6, 12, 13};
                    while (poz[0] == poz[1]){
                        poz[1] = rand()%4;
                    }
                    while (poz[3] == poz[4] || poz[3] == poz[5] || poz[4] == poz[5]){
                        if(poz[3] == poz[4])
                            poz[4] = 6+rand()%6;
                        else if (poz[3] == poz[5])
                                poz[3] = 6+rand()%6;
                        else{
                            poz[5] = 6+rand()%6;
                        }
                    }

                    std::unique_ptr <int[]> tmp(new int[8]);
                    for(auto i=0; i<8; i++){
                        auto rnd = 1 + rand()%8;
                        tmp[i] = rnd;
                        for(auto j=0; j<i; j++){
                            if (rnd == tmp[j]){
                                i--;
                                break;
                            }
                        }
                    }

                    cactus[poz[0]].setposition(1080*tmp[0]+rand()%540, 325);
                    cactus[poz[1]].setposition(1080*tmp[1]+rand()%540, 325);
                    cactus[poz[2]].setposition(1080*tmp[2]+rand()%540, 304);
                    cactus[poz[3]].setposition(1080*tmp[3]+rand()%540, 325);
                    cactus[poz[4]].setposition(1080*tmp[4]+rand()%540, 325);
                    cactus[poz[5]].setposition(1080*tmp[5]+rand()%540, 325);
                    cactus[12].setposition(1080*tmp[6]+rand()%540, 304);
                    cactus[13].setposition(1080*tmp[7]+rand()%540, 304);

                    ///collision system cactusi TBD

                    /*
                    for (int i=0; i<abs(poz.size()-1); i++){
                        bool repeat = false;
                        for (int j=i+1; j<abs(poz.size()); j++){
                            while (cactus[poz[i]].getposition().getx() > cactus[poz[j]].getposition().getx() - cactus[poz[i]].gettexture()->getSize().x - 300 &&
                                   cactus[poz[i]].getposition().getx() < cactus[poz[j]].getposition().getx() + cactus[poz[j]].gettexture()->getSize().x + 300){
                                cactus[poz[i]].setpositionx(1080+rand()%(1080*4));
                                repeat = true;
                            }
                            if (repeat)
                                j=i;
                            repeat = false;
                        }
                    }
                    */

                }

                if (pos>=10){
                    img = true;
                    bird->settexture2("textures/" + theme + "/bird 1.png");
                    if (!dino->getj()){
                        if (!dino->getd()){
                            dino->settexture2("textures/" + theme + "/dino move 1.png");
                        }
                        else dino->settexture2("textures/" + theme + "/dino down 1.png");
                    }
                }
                else if(pos<=0){
                    img = false;
                    bird->settexture2("textures/" + theme + "/bird 2.png");
                    if (!dino->getj()){
                         if (!dino->getd()){
                            dino->settexture2("textures/" + theme + "/dino move 2.png");
                         }
                         else dino->settexture2("textures/" + theme + "/dino down 2.png");
                    }
                }
                if (img){
                    pos -= 60.0/frames * speedMultiplier * slowdown/4;
                }
                else{
                    pos += 60.0/frames * speedMultiplier * slowdown/4;
                }

                score += (0.4*pow(1.1, (difchg-1000)/1000)) * 60.0/frames * speedMultiplier * slowdown/4;
                scor<<(int)(score);

                if (score+1>nr){
                    nr *= 10;
                    width -= 18;
                }

                if(dino->getj() && dino->getposition().gety()<305){
                    dino->setspeed(dino->getspeed() + v*60/frames);
                    dino->Move();
                }
                if (dino->getposition().gety()>305){
                    v = -60.0/frames;
                    dino->setj(false);
                    dino->setpositiony(305);
                    dino->setspeed(0);
                }
                if (dino->getposition().gety()<=225){
                    v = 60.0/frames;
                }

                setcaract_text <int, float> (text, font, scor, theme, 30, width, 0);

                ///collision system
                if(!isCheatActivated){
                    ///cactusi
                    if (poz[7]){
                        bool colided=false;
                        if (!dino->getd()){
                            for(int i=0; i<8; i++){
                                if (dino->getposition().getx() + 64 > cactus[poz[i]].getposition().getx() &&
                                    dino->getposition().getx() < cactus[poz[i]].getposition().getx() + cactus[poz[i]].gettexture()->getSize().x - 7 &&
                                    dino->getposition().gety() + 72 > cactus[poz[i]].getposition().gety()){
                                    colided = true;
                                    break;
                                }
                            }
                        }
                        else{
                            for(int i=0; i<8; i++){
                                if (dino->getposition().getx() + 84 > cactus[poz[i]].getposition().getx() &&
                                    dino->getposition().getx() < cactus[poz[i]].getposition().getx() + cactus[poz[i]].gettexture()->getSize().x){
                                    colided = true;
                                    break;
                                }
                            }
                        }
                        if (colided){
                            if (theme == "dark theme"){
                                window->clear();
                            }
                            else{
                                window->clear(Color::White);
                            }

                            window->draw(background.getsprite());
                            window->draw(pre_background.getsprite());
                            if (theme == "dark theme"){
                                window->draw(moon->getsprite());
                            }
                            if (theme == "dark theme"){
                                for (int i=0; i<9; i++){
                                    stars[i].Move();
                                    if (stars[i].getposition().getx() < -25){
                                        stars[i].setposition(rand()%1080, 25+rand()%150);
                                    }
                                    window->draw(stars[i].getsprite());
                                }
                            }
                            for(int i=0; i<14; i++){
                                if (cactus[i].getposition().getx() >= -125)
                                    cactus[i].Move();
                                if (cactus[i].getposition().getx() < 1280)
                                    window->draw(cactus[i].getsprite());
                            }
                            dino->settexture2("textures/" + theme + "/dino dead.png");
                            dino->setpositionx(dino->getposition().getx() + 10);
                            window->draw(dino->getsprite());
                            window->draw(bird->getsprite());
                            window->draw(cloud1->getsprite());
                            window->draw(cloud2->getsprite());
                            window->draw(text);

                            window->display();

                            Sleep(1000);

                            float v = -120.0/frames;
                            dino->setspeed(0);

                            while (dino->getposition().gety() < 750){
                                while (window->pollEvent(event)){
                                    switch(event.type){
                                        case Event::Closed:
                                            return false;
                                        default:{}
                                    }
                                }
                                if (theme == "dark theme"){
                                    window->clear();
                                }
                                else{
                                    window->clear(Color::White);
                                }

                                window->draw(background.getsprite());
                                window->draw(pre_background.getsprite());
                                if (theme == "dark theme"){
                                    window->draw(moon->getsprite());
                                }
                                for(int i=0; i<14; i++){
                                    if (cactus[i].getposition().getx() < 1080){
                                        window->draw(cactus[i].getsprite());
                                    }
                                    if (i<9 && theme == "dark theme"){
                                        window->draw(stars[i].getsprite());
                                    }
                                }

                                dino->setspeed(dino->getspeed() + v);
                                dino->Move();

                                window->draw(dino->getsprite());
                                window->draw(bird->getsprite());
                                window->draw(cloud1->getsprite());
                                window->draw(cloud2->getsprite());
                                window->draw(text);

                                window->display();

                                if (dino->getposition().gety()<=200){
                                    v = 120.0/frames;
                                }
                            }

                            Vector2u windowSize = window->getSize();
                            Texture tmp;
                            tmp.create(windowSize.x, windowSize.y);
                            tmp.update(*window);
                            Image aux = tmp.copyToImage();
                            aux.saveToFile("textures/deathscreen.png");

                            Sleep(100);

                            if (theme == "dark theme"){
                                window->clear();
                            }
                            else{
                                window->clear(Color::White);
                            }

                            background.setpositionx(0);

                            tmp.loadFromImage(aux);
                            background.settexture(tmp);

                            window->draw(background.getsprite());

                            window->display();

                            if (highscore < int(score)){
                                highscore = int(score);

                                std::ifstream f("config.txt");
                                std::string settings;
                                getline(f, settings);
                                getline(f, settings);
                                f.close();

                                std::ofstream g("config.txt");
                                std::string aux;
                                aux = scor.str();
                                for(int i=0; i<abs(aux.length()); i++){
                                    aux[i] += 81;
                                }
                                g<<aux<<'\n';
                                g<<settings;
                                g.close();
                            }

                            scor.str("");

                            Sleep(100);

                            if (theme == "dark theme"){
                                moon->setposition(1080+rand()%500, 5+rand()%50);
                            }
                            bird->setposition(3240+rand()%1080, 62+rand()%238);
                            cloud1->setposition(1080+rand()%540, 25+rand()%125);
                            cloud2->setposition(1620+rand()%540, 25+rand()%125);

                            delete button;
                            delete bolt;

                            return true;
                        }
                    }

                    ///pasare
                    if (bird->getposition().getx() < 1080){
                        bool colided=false;
                        if(img){
                            if (dino->getposition().getx() + 59 > bird->getposition().getx() &&
                                dino->getposition().getx() < bird->getposition().getx() + bird->gettexture()->getSize().x + 8 &&
                                dino->getposition().gety() + 72 > bird->getposition().gety() + 10 &&
                                dino->getposition().gety() < bird->getposition().gety() + bird->gettexture()->getSize().y){
                                    colided = true;
                                }
                        }
                        else{
                            if (dino->getposition().getx() + 59 > bird->getposition().getx() &&
                                dino->getposition().getx() < bird->getposition().getx() + bird->gettexture()->getSize().x + 8 &&
                                dino->getposition().gety() + 72 > bird->getposition().gety() &&
                                dino->getposition().gety() < bird->getposition().gety() + bird->gettexture()->getSize().y - 16){
                                    colided = true;
                                }
                        }

                        if(colided){
                            if (theme == "dark theme"){
                                window->clear();
                            }
                            else{
                                window->clear(Color::White);
                            }

                            window->draw(background.getsprite());
                            window->draw(pre_background.getsprite());
                            if (theme == "dark theme"){
                                window->draw(moon->getsprite());
                            }

                            if (theme == "dark theme"){
                                for (int i=0; i<9; i++){
                                    stars[i].Move();
                                    if (stars[i].getposition().getx() < -25){
                                        stars[i].setposition(rand()%1080, 25+rand()%150);
                                    }
                                    window->draw(stars[i].getsprite());
                                }
                            }
                            for(int i=0; i<14; i++){
                                if (cactus[i].getposition().getx() >= -125)
                                    cactus[i].Move();
                                if (cactus[i].getposition().getx() < 1280)
                                    window->draw(cactus[i].getsprite());
                            }

                            window->draw(bird->getsprite());
                            window->draw(cloud1->getsprite());
                            window->draw(cloud2->getsprite());
                            window->display();

                            window->display();

                            Vector2u windowSize = window->getSize();
                            Texture tmp;
                            tmp.create(windowSize.x, windowSize.y);
                            tmp.update(*window);
                            Image aux = tmp.copyToImage();
                            aux.saveToFile("textures/deathscreen.png");

                            dino->setpositiony(600);

                            if (highscore < int(score)){
                                highscore = int(score);

                                std::ifstream f("config.txt");
                                std::string settings;
                                getline(f, settings);
                                getline(f, settings);
                                f.close();

                                std::ofstream g("config.txt");
                                std::string aux;
                                aux = scor.str();
                                std::for_each(aux.begin(), aux.end(), [](char &i){
                                    i += 81;
                                });
                                g<<aux<<'\n';
                                g<<settings;
                                g.close();
                            }

                            scor.str("");

                            Sleep(250);

                            if (theme == "dark theme"){
                                moon->setposition(1080+rand()%500, 5+rand()%50);
                            }
                            bird->setposition(3240+rand()%1080, 62+rand()%238);
                            cloud1->setposition(1080+rand()%540, 25+rand()%125);
                            cloud2->setposition(1620+rand()%540, 25+rand()%125);

                            delete button;
                            delete bolt;

                            return true;
                        }
                    }

                }

                if (theme == "dark theme"){
                    window->clear();
                }
                else{
                    window->clear(Color::White);
                }

                window->draw(background.getsprite());
                window->draw(pre_background.getsprite());
                if (theme == "dark theme"){
                    window->draw(moon->getsprite());
                }

                if (theme == "dark theme"){
                    ///parcurgere STL cu lambda function
                    std::for_each(stars.begin(), stars.end(), [&](Stars &i){
                        i.Move();
                        if (i.getposition().getx() < -25){
                            i.setposition(rand()%1080, 25+rand()%150);
                        }
                        window->draw(i.getsprite());
                    });
                }

                ///parcurgere STL cu iterator --- *i - dereferentiere iterator
                for(std::vector<Cactus>::iterator i = cactus.begin(); i<cactus.end(); i++){
                    if ((*i).getposition().getx() >= -125)
                        (*i).Move();
                    if ((*i).getposition().getx() < 1280)
                        window->draw((*i).getsprite());
                }

                window->draw(dino->getsprite());
                window->draw(bird->getsprite());
                window->draw(cloud1->getsprite());
                window->draw(cloud2->getsprite());
                window->draw(text);
                window->draw(text_hi);
                window->draw(button->getsprite());

                if (bolt->get_o()){
                    bolt->Move();
                    window->draw(bolt->getsprite());
                }

                if (bolt->getposition().getx() > 1080){
                    bolt->set_o(false);
                    bolt->getposition().setx(-500);
                }

                ///detection bolt-bird
                if (bolt->getposition().getx() + 10 > bird->getposition().getx() &&
                    bolt->getposition().getx() < bird->getposition().getx() + bird->gettexture()->getSize().x &&
                    bolt->getposition().gety() + 7 > bird->getposition().gety() &&
                    bolt->getposition().gety() < bird->getposition().gety() + 62){
                    bolt->set_o(false);
                    bolt->getposition().setx(-500);
                    bird->setposition(-71, bird->getposition().gety());
                }

                ///detection bolt-cactus
                std::for_each(cactus.begin(), cactus.end(), [&](const Cactus &i){
                    if (bolt->getposition().getx() + 15 > i.getposition().getx() &&
                        bolt->getposition().getx() < i.getposition().getx() + i.gettexture()->getSize().x &&
                        bolt->getposition().gety() + 15 > i.getposition().gety() &&
                        bolt->getposition().gety() < i.getposition().gety() + i.gettexture()->getSize().y){
                            bolt->set_o(false);
                            bolt->getposition().setx(-500);
                    }
                });

                dt = clock.restart().asSeconds();
                fps<<(int)(1/dt); ///c-style cast

                setcaract_text <int, float> (text_fps, font, fps, theme, 25, 0, 0);

                if (showfps){
                    window->draw(text_fps);
                }

                if (showTips){
                    if (tipsShown[2]){
                        window->draw(tips[0]);
                    }
                    else if (tipsShown[3]){
                        window->draw(tips[1]);
                        window->draw(tips[2]);
                    }
                }

                window->display();

                scor.str("");
                fps.str("");

                Sleep(0.001);
            }
        }

        return false;
    }

    bool Deathscreen(){
        Button *button = button->getInstance("textures/" + theme + "/settings.png", 0, 520, 25);
        std::unique_ptr <Background> background(new Background("textures/deathscreen.png", 0) );

        Text text;
        Font font;
        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            std::cout<<"Error loading file!"<<std::endl;
            window->close();
            exit(EXIT_FAILURE);
            return false;
        }

        setcaract_text <int, float> (text, font, static_cast<std::ostringstream>("Press\tSPACE\tor\tLEFT\tCLICK\tto\trestart"), theme, 40, 140, 100);

        while(window->isOpen()){
            Event event;
            while (window->pollEvent(event)){
                switch(event.type){
                    case Event::Closed:
                        return false;
                    case Event::KeyPressed:
                        if (event.key.code == Keyboard::Space){
                            delete button;

                            Sleep(100);

                            return true;
                        }
                        else if (event.key.code == Keyboard::Tilde){
                            if (isCheatActivated){
                                isCheatActivated = false;
                            }
                            else{
                                isCheatActivated = true;
                            }
                        }
                        break;
                    case Event::MouseButtonPressed:
                        if (event.mouseButton.button == Mouse::Left){
                            Vector2f mouse = window->mapPixelToCoords(Mouse::getPosition(*window));
                            FloatRect bound = button->getsprite().getGlobalBounds();
                            if (!bound.contains(mouse)){
                                delete button;

                                Sleep(100);

                                return true;
                            }
                            else{
                                delete button;

                                std::string aux = "textures/" + theme + "/settings.png";

                                window->setActive(false);
                                window->setVisible(false);

                                Settings();

                                window->setVisible(true);
                                window->setActive(true);

                                button->getInstance(aux, 0, 520, 25);
                            }
                        }
                        break;
                    default:{}
                }
            }
            window->clear();

            window->draw(background->getsprite());
            window->draw(button->getsprite());
            window->draw(text);

            window->display();

            Sleep(0.001);
        }

        return false;
    }


    void set_highscore(int x){
        highscore = x;
    }
    void set_score(int x){
        score = x;
    }
    void set_cheat(bool x){
        isCheatActivated = x;
    }
    void set_frames(int x){
        frames = x;
    }
    void set_window(RenderWindow* x){
        window = x;
    }
    void set_fps(bool x){
        showfps = x;
    }
    void set_theme(std::string x){
        theme = x;
    }
    void set_tips(bool x){
        showTips = x;
    }
    void set_multiplier(float x){
        speedMultiplier = x;
    }
    void set_s (bool x){
        isShooting = x;
    }


    int get_highscore() const{
        return highscore;
    }
    int get_score() const{
        return score;
    }
    bool get_cheat() const{
        return isCheatActivated;
    }
    int get_frames() const{
        return frames;
    }
    RenderWindow* get_window() const{
        return window;
    }
    bool get_fps() const{
        return showfps;
    }
    std::string get_theme() const{
        return theme;
    }
    bool get_t() const{
        return showTips;
    }
    float get_m() const{
        return speedMultiplier;
    }
    bool get_s() const{
        return isShooting;
    }
};
App* App::object=0;

int main()
{
    App *app=app->getInstance(1080, 500, "T-Rex game", 60, false, true, "textures/dino.png");
    bool ok;

    if (app->Homescreen()){
        ok = true;
        while (ok){
            if (app->Game()){
                if (!app->Deathscreen()){
                    ok = false;
                }
            }
            else{
                ok = false;
            }
        }
    }

    return 0;
}
