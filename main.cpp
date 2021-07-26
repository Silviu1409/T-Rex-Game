#include <SFML/Graphics.hpp>
#include <sstream>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace sf;

void setcaract_text(Text &text, const Font& font, const std::ostringstream& ss, const int font_size = 1, const float x = 0, const float y = 0){
    text.setFont(font);
    text.setString(ss.str());
    text.setCharacterSize(font_size);
    text.setPosition(x, y);
    text.setFillColor(Color::White);
    text.setStyle(Text::Bold);
}

class point{
    float x;
    float y;
public:
    point(float a=0, float b=0){x = a, y = b;}
    ~point(){x = 0, y = 0;}
    void setx(float a){x = a;}
    void sety(float b){y = b;}
    float getx() const {return x;}
    float gety() const {return y;}
};

class Background{
    point position;
    Texture *t;
    float speed;
protected:
    Sprite s;
public:
    Background(){
        position.setx(0);
        position.sety(0);
        t = new Texture;
        t->create(1, 1);
        speed = 0;
        s.setTexture(*t);
        s.setPosition(0, 0);
    }
    Background(point pozitie, std::string sursa, float v){
        position.setx(pozitie.getx());
        position.sety(pozitie.gety());
        t = new Texture;
        t->loadFromFile(sursa);
        speed = v;
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    Background(std::string sursa, float v, float x=0, float y=0){
        position.setx(x);
        position.sety(y);
        t = new Texture;
        t->loadFromFile(sursa);
        speed = v;
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    Background(point pozitie, Texture textura, float v, float x = 0, float y = 0){
        position.setx(pozitie.getx());
        position.sety(pozitie.gety());
        t = new Texture(textura);
        speed = v;
        s.setTexture(*t);
        s.setPosition(position.getx(), position.gety());
    }
    virtual ~Background(){
        position.setx(0);
        position.sety(0);
        t=0;
        speed = 0;
        s.setTexture(*t);
        s.setPosition(0, 0);
    }

    virtual void Move(){
        this->setpositionx(this->getposition().getx() + this->getspeed());
    }

    void setposition(point pozitie){
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
        s.setTexture(*t);
    }
    void settexture2(std::string sursa){
        Texture aux;
        aux.loadFromFile(sursa);
        t->swap(aux);
        s.setTexture(*t);
    }
    void setsprite(Sprite sprite){
        s = sprite;
    }
    void setsprite(Texture texture){
        s.setTexture(texture);
        s.setPosition(0, 0);
    }
    void setspeed(float v){
        speed = v;
    }

    point getposition() const{
        return position;
    }
    Texture* gettexture() const{
        return t;
    }
    Sprite getsprite() const{
        return s;
    }
    float getspeed() const{
        return speed;
    }

};

class Cactus:public Background{
public:
    Cactus():Background(){};
    Cactus(point pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Cactus(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Cactus(point pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
    ~Cactus(){};
};

class Cloud:public Background{
    static Cloud *object1;
    static Cloud *object2;
    Cloud():Background(){};
    Cloud(point pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Cloud(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Cloud(point pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
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

    ~Cloud(){};
};
Cloud* Cloud::object1=0;
Cloud* Cloud::object2=0;

class Moon:public Background{
    static Moon *object;
    Moon():Background(){};
    Moon(point pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Moon(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Moon(point pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
public:
    static Moon* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Moon(sursa, v, x, y);
        return object;
    }
    ~Moon(){};
};
Moon* Moon::object=0;

class Stars:public Background{
public:
    Stars():Background(){};
    Stars(point pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Stars(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Stars(point pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
    ~Stars(){};
};

class Bird:public Background{
    static Bird *object;
    Bird():Background(){};
    Bird(point pozitie, std::string sursa, float v):Background(pozitie, sursa, v){};
    Bird(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){};
    Bird(point pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){};
public:
    static Bird* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Bird(sursa, v, x, y);
        return object;
    }

    ~Bird(){};
};
Bird* Bird::object=0;

class Dino:public Background{
    static Dino *object;
    Dino():Background(){
        isJumping = false;
    }
    Dino(point pozitie, std::string sursa, float v):Background(pozitie, sursa, v){
        isJumping = false;
    }
    Dino(std::string sursa, float v, float x=0, float y=0):Background(sursa, v, x, y){
        isJumping = false;
    }
    Dino(point pozitie, Texture textura, float v, float x = 0, float y = 0):Background(pozitie, textura, v, x, y){
        isJumping = false;
    }
    bool isJumping;
public:
    static Dino* getInstance(std::string sursa, float v, float x=0, float y=0){
        if(!object)
            object=new Dino(sursa, v, x, y);
        return object;
    }

    ~Dino(){
        isJumping = false;
    }

    void Move(){
        this->setpositiony(this->getposition().gety() + this->getspeed());
    }

    void setj(bool x){
        isJumping = x;
    }
    bool getj() const{
        return isJumping;
    }

};
Dino* Dino::object=0;

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
        }
        highscore = 0;
        score = 0;
        isCheatActivated = false;
        frames = fps;
    }
   	RenderWindow* window;
   	float score;
   	int highscore;
   	bool isCheatActivated;
   	int frames;
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
    }

    bool Homescreen(){
        Background background("textures/background homescreen.png", 0);
        Dino *dino = dino->getInstance("textures/dino start.png", 0, 50, 305);

        Text text;
        Font font;
        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            window->close();
            return false;
        }

        setcaract_text(text, font, static_cast<std::ostringstream>("Press\tSPACE\tor\tLEFT\tCLICK\tto\tbegin"), 40, 150, 100);

        window->clear();
        window->draw(background.getsprite());
        window->draw(dino->getsprite());
        window->draw(text);
        window->display();
        window->setFramerateLimit(frames);

        int pos = 0;
        bool img = false;

        while(window->isOpen()){
            Event event;
            while (window->pollEvent(event)){
                switch(event.type){
                    case Event::Closed:
                        window->close();
                    case Event::KeyReleased:
                        if (event.key.code == Keyboard::Space){
                            window->clear();
                            window->setFramerateLimit(frames);
                            window->draw(background.getsprite());
                            dino->settexture2("textures/dino static.png");
                            window->draw(dino->getsprite());
                            window->display();
                            float v = -60.0/frames;
                            while(dino->getposition().gety()<=305){
                                window->clear();
                                window->draw(background.getsprite());
                                dino->setspeed(dino->getspeed() + v);
                                dino->Move();
                                window->draw(dino->getsprite());
                                window->display();
                                if (dino->getposition().gety()<=225){
                                    v = 60.0/frames;
                                }
                            }
                            Sleep(0.01);
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
                            window->clear();
                            window->setFramerateLimit(frames);
                            window->draw(background.getsprite());
                            dino->settexture2("textures/dino static.png");
                            window->draw(dino->getsprite());
                            window->display();
                            float v = -60.0/frames;
                            while(dino->getposition().gety()<=305){
                                window->clear();
                                window->draw(background.getsprite());
                                dino->setspeed(dino->getspeed() + v);
                                dino->Move();
                                window->draw(dino->getsprite());
                                window->display();
                                if (dino->getposition().gety()<=225){
                                    v = 60.0/frames;
                                }
                            }
                            Sleep(0.01);
                            return true;
                        }
                        else if (event.mouseButton.button == Mouse::Middle){
                            if (isCheatActivated){
                                isCheatActivated = false;
                            }
                            else{
                                isCheatActivated = true;
                            }
                        }
                    default:{}
                }
            }

            if (pos==10){
                img = true;
                dino->settexture2("textures/dino start 1.png");
            }
            else if(pos==0){
                img = false;
                dino->settexture2("textures/dino start 2.png");
            }
            if (img){
                pos--;
            }
            else pos++;

            window->clear();
            window->draw(background.getsprite());
            window->draw(dino->getsprite());
            window->draw(text);
            window->display();

            Sleep(0.01);
        }
        return false;
    }
    void Settings(){
        //TBD
    }
    bool Game(){
        window->clear();
        window->setFramerateLimit(frames);

        srand(time(0));

        ///get highscore from file
        std::ifstream f("highscore.txt");
        std::string aux;
        getline(f, aux);
        if (aux != ""){
            for(int i=0; i<aux.length(); i++)
                aux[i] -= 81;
            std::stringstream tmp(aux);
            tmp>>highscore;
        }

        Background background("textures/background.png", -420.0/frames), pre_background("textures/background.png", -420.0/frames, 2400);
        Dino *dino = dino->getInstance("textures/dino static.png", 0, 50, 305);
        Moon *moon = moon->getInstance("textures/moon.png", -60.0/frames, 1080+rand()%500, 5+rand()%50);
        std::string x;
        std::vector <Stars> stars;
        for (int i=0; i<3; i++){
            x = "textures/star "+std::to_string(i+1)+".png";
            Stars tmp(x, -60.0/frames, i*300 + rand()%180, 25+rand()%150);
            stars.push_back(tmp);
            tmp.setposition(i*300 + rand()%180, 25+rand()%150);
            stars.push_back(tmp);
            tmp.setposition(i*300 + rand()%180, 25+rand()%150);
            stars.push_back(tmp);
        }

        Bird *bird = bird->getInstance("textures/bird 1.png", -300.0/frames, 3240+rand()%1080, 62+rand()%238);
        Cloud *cloud1 = cloud1->getInstance("textures/cloud.png", -75.0/frames, 1080+rand()%540, 25+rand()%125);
        Cloud *cloud2 = cloud2->getInstance("textures/cloud.png", -75.0/frames, 1620+rand()%540, 25+rand()%125);

        std::vector <Cactus> cactus;
        for (int i=0; i<14; i++){
            x = "textures/cactus "+std::to_string(i+1)+".png";
            Cactus tmp(x, -420.0/frames, 1081, 501);
            cactus.push_back(tmp);
        }

        set_score(0);

        Text text, text_hi;
        Font font;
        std::ostringstream scor;
        std::ostringstream high_scor;

        if(!font.loadFromFile("res/ARCADECLASSIC.ttf")){
            std::cout<<"Error loading file!"<<std::endl;
            window->close();
            return false;
        }

        scor<<score;
        high_scor<<"HI\t"<<highscore;
        setcaract_text(text, font, scor, 30, 1060, 0);
        int tmp = highscore;
        int p=0;
        while (tmp>9){
            tmp /= 10;
            p++;
        }
        setcaract_text(text_hi, font, high_scor, 30, 1000 - 17*p, 30);
        window->draw(background.getsprite());
        window->draw(dino->getsprite());
        window->draw(text);
        window->draw(text_hi);
        for (int i=0; i<3; i++){
            window->draw(stars[i].getsprite());
        }
        window->display();
        scor.str("");

        int pos = 0;
        bool img = false;
        int nr=10;
        int width = 1060;
        float v = -60.0/frames;
        bool isdinodown = false;
        float renderDistance = 1080.0;
        std::vector <int> poz={0,0,0,0,0,0,0,0};
        int difchg = 1000;

        while (window->isOpen())
        {
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
                                dino->settexture2("textures/dino static.png");
                            }
                        }
                        else if (event.key.code == Keyboard::Down){
                            isdinodown = true;
                            window->setKeyRepeatEnabled(true);
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
                            if (!dino->getj()){
                                dino->setj(true);
                                dino->setpositiony(dino->getposition().gety()+v);
                                dino->settexture2("textures/dino static.png");
                            }
                        }
                        else if (event.mouseButton.button == Mouse::Right){
                            isdinodown = true;
                            window->setKeyRepeatEnabled(true);
                        }
                        else if (event.mouseButton.button == Mouse::Middle){
                            if (isCheatActivated){
                                isCheatActivated = false;
                            }
                            else{
                                isCheatActivated = true;
                            }
                        }
                        break;
                    case Event::KeyReleased:
                        if (event.key.code == Keyboard::Down){
                            isdinodown = false;
                            window->setKeyRepeatEnabled(false);
                        }
                        break;
                    case Event::MouseButtonReleased:
                        if (event.mouseButton.button == Mouse::Right){
                            isdinodown = false;
                            window->setKeyRepeatEnabled(false);
                        }
                        break;
                    default:{}
                }
            }

            if (background.getposition().getx() < -2400){
                background.setpositionx(2400);
            }
            else if (pre_background.getposition().getx() < -2400){
                pre_background.setpositionx(2400);
            }

            if (moon->getposition().getx() < -30){
                moon->setposition(1280+rand()%500, 5+rand()%50);
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
                pre_background.setspeed(background.getspeed()*1.1);
                moon->setspeed(moon->getspeed()*1.1);
                cloud1->setspeed(cloud1->getspeed()*1.1);
                cloud2->setspeed(cloud2->getspeed()*1.1);
                bird->setspeed(bird->getspeed()*1.1);
                for (int i=0; i<14; i++){
                    cactus[i].setspeed(cactus[i].getspeed()*1.1);
                }
            }

            background.Move();
            pre_background.Move();
            moon->Move();
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
                cactus[poz[0]].setposition(1080+rand()%1080, 325);
                cactus[poz[1]].setposition(1080*5+rand()%1080, 325);
                cactus[poz[2]].setposition(1080*2+rand()%1080, 304);
                cactus[poz[3]].setposition(1080*6+rand()%1080, 325);
                cactus[poz[4]].setposition(1080*8+rand()%1080, 325);
                cactus[poz[5]].setposition(1080*3+rand()%1080, 325);
                cactus[12].setposition(1080*4+rand()%1080, 304);
                cactus[13].setposition(1080*7+rand()%1080, 304);

                ///collision system cactusi TBD

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

            }

            if (pos==10){
                img = true;
                bird->settexture2("textures/bird 1.png");
                if (!dino->getj()){
                    if (!isdinodown){
                        dino->settexture2("textures/dino move 1.png");
                    }
                    else dino->settexture2("textures/dino down 1.png");
                }
            }
            else if(pos==0){
                img = false;
                bird->settexture2("textures/bird 2.png");
                if (!dino->getj()){
                     if (!isdinodown){
                        dino->settexture2("textures/dino move 2.png");
                     }
                     else dino->settexture2("textures/dino down 2.png");
                }
            }
            if (img){
                pos--;
            }
            else pos++;
            score += (0.4*pow(1.1, (difchg-1000)/1000));
            scor<<(int)(score);
            if (score+1>nr){
                nr *= 10;
                width -= 18;
            }

            if(dino->getj() && dino->getposition().gety()<305){
                dino->setspeed(dino->getspeed() + v);
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

            setcaract_text(text, font, scor, 30, width, 0);

            ///collision system
            if(!isCheatActivated){
                ///cactusi
                if (poz[7]){
                    bool colided=false;
                    if (!isdinodown){
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
                        window->clear();
                        window->draw(background.getsprite());
                        window->draw(pre_background.getsprite());
                        window->draw(moon->getsprite());
                        for (int i=0; i<9; i++){
                            stars[i].Move();
                            if (stars[i].getposition().getx() < -25){
                                stars[i].setposition(rand()%1080, 25+rand()%150);
                            }
                            window->draw(stars[i].getsprite());
                        }
                        for(int i=0; i<14; i++){
                            if (cactus[i].getposition().getx() >= -125)
                                cactus[i].Move();
                            if (cactus[i].getposition().getx() < 1280)
                                window->draw(cactus[i].getsprite());
                        }
                        dino->settexture2("textures/dino dead.png");
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
                            window->clear();
                            window->draw(background.getsprite());
                            window->draw(pre_background.getsprite());
                            window->draw(moon->getsprite());
                            for(int i=0; i<14; i++){
                                if (cactus[i].getposition().getx() < 1080)
                                    window->draw(cactus[i].getsprite());
                                if (i<9)
                                    window->draw(stars[i].getsprite());
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

                        Texture aux;
                        aux.create(window->getSize().x, window->getSize().y);
                        aux.update(*window);
                        aux.copyToImage().saveToFile("textures/deathscreen.png");

                        Sleep(100);

                        window->clear();

                        background.setpositionx(0);
                        background.settexture2("textures/deathscreen.png");
                        window->draw(background.getsprite());
                        setcaract_text(text, font, static_cast<std::ostringstream>("Press\tSPACE\tor\tLEFT\tCLICK\tto\trestart"), 40, 140, 100);
                        window->draw(text);
                        window->display();

                        if (highscore < int(score)){
                            highscore = int(score);
                            std::ofstream g("highscore.txt");
                            std::string aux;
                            aux = scor.str();
                            for(int i=0; i<aux.length(); i++){
                                aux[i] += 81;
                            }
                            g<<aux;
                            g.close();
                        }

                        scor.str("");

                        Sleep(1000);

                        moon->setposition(1080+rand()%500, 5+rand()%50);
                        bird->setposition(3240+rand()%1080, 62+rand()%238);
                        cloud1->setposition(1080+rand()%540, 25+rand()%125);
                        cloud2->setposition(1620+rand()%540, 25+rand()%125);

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
                        window->clear();
                        window->draw(background.getsprite());
                        window->draw(pre_background.getsprite());
                        window->draw(moon->getsprite());
                        for (int i=0; i<9; i++){
                            stars[i].Move();
                            if (stars[i].getposition().getx() < -25){
                                stars[i].setposition(rand()%1080, 25+rand()%150);
                            }
                            window->draw(stars[i].getsprite());
                        }
                        for(int i=0; i<14; i++){
                            if (cactus[i].getposition().getx() >= -125)
                                cactus[i].Move();
                            if (cactus[i].getposition().getx() < 1280)
                                window->draw(cactus[i].getsprite());
                        }
                        dino->settexture2("textures/dino dead.png");
                        window->draw(dino->getsprite());
                        window->draw(bird->getsprite());
                        window->draw(cloud1->getsprite());
                        window->draw(cloud2->getsprite());
                        setcaract_text(text, font, static_cast<std::ostringstream>("Press\tSPACE\tor\tLEFT\tCLICK\tto\trestart"), 40, 140, 100);
                        window->draw(text);
                        window->display();

                        dino->setpositiony(600);

                        if (highscore < int(score)){
                            highscore = int(score);
                            std::ofstream g("highscore.txt");
                            std::string aux;
                            aux = scor.str();
                            for(int i=0; i<aux.length(); i++){
                                aux[i] += 81;
                            }
                            g<<aux;
                            g.close();
                        }

                        scor.str("");

                        Sleep(1000);

                        moon->setposition(1080+rand()%500, 5+rand()%50);
                        bird->setposition(3240+rand()%1080, 62+rand()%238);
                        cloud1->setposition(1080+rand()%540, 25+rand()%125);
                        cloud2->setposition(1620+rand()%540, 25+rand()%125);

                        return true;
                    }
                }

            }

            window->clear();
            window->draw(background.getsprite());
            window->draw(pre_background.getsprite());
            window->draw(moon->getsprite());
            for (int i=0; i<9; i++){
                stars[i].Move();
                if (stars[i].getposition().getx() < -25){
                    stars[i].setposition(rand()%1080, 25+rand()%150);
                }
                window->draw(stars[i].getsprite());
            }
            for(int i=0; i<14; i++){
                if (cactus[i].getposition().getx() >= -125)
                    cactus[i].Move();
                if (cactus[i].getposition().getx() < 1280)
                    window->draw(cactus[i].getsprite());
            }
            window->draw(dino->getsprite());
            window->draw(bird->getsprite());
            window->draw(cloud1->getsprite());
            window->draw(cloud2->getsprite());
            window->draw(text);
            window->draw(text_hi);
            window->display();

            scor.str("");

            Sleep(0.01);
        }

        return false;

    }
    bool Deathscreen(){

        window->setFramerateLimit(0);

        while(window->isOpen()){
            Event event;
            while (window->pollEvent(event)){
                switch(event.type){
                    case Event::Closed:
                        return false;
                    case Event::KeyPressed:
                        if (event.key.code == Keyboard::Space){
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
                    case Event::MouseButtonPressed:
                        if (event.mouseButton.button == Mouse::Left){
                            Sleep(100);
                            return true;
                        }
                        else if (event.mouseButton.button == Mouse::Middle){
                            if (isCheatActivated){
                                isCheatActivated = false;
                            }
                            else{
                                isCheatActivated = true;
                            }
                        }
                    default:{}
                }
            }
            Sleep(0.01);
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

};
App* App::object=0;

int main()
{
    App *app=app->getInstance(1080, 500, "T-Rex game", 60, false, true, "textures/dino static.png");
    if (app->Homescreen()){
        bool ok = true;
        while (ok){
            if (app->Game()){
                if (!app->Deathscreen()){
                    ok = false;
                }
            }
            else ok = false;
        }
    }
    return 0;
}
