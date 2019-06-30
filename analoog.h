#ifndef MO_
#define MO_


class mo {
  private:
    int pin1_;
    int pin2_;


  public:
    mo() {}
    mo(int pin1, int pin2) {
      pin1_ = pin1;
      pin2_ = pin2;
    }
    void run(int speed) {
      if (speed >= 0) {
        analogWrite(pin1_, speed);
        analogWrite(pin2_, 0);
      }
      if (speed <= 0) {
        analogWrite(pin1_, 0);
        analogWrite(pin2_, -speed);
      }
    }
};
class omuni {
    private:
     mo m0_,m1_,m2_,m3_;
    
    public:
    omuni(mo m0, mo m1, mo m2, mo m3) {
      m0_ = m0;
      m1_ = m1;
      m2_ = m2;
      m3_ = m3;
    }
    void right(int speed) {
      m0_.run(speed);
      m1_.run(-speed);
      m2_.run(-speed);
      m3_.run(speed);
    }
    void left(int speed) {
      m0_.run(-speed);
      m1_.run(speed);
      m2_.run(speed);
      m3_.run(-speed);
    }
    void forward(int speed) {
      m0_.run(-speed);
      m1_.run(-speed);
      m2_.run(speed);
      m3_.run(speed);
    }
    void back(int speed) {
      m0_.run(speed);
      m1_.run(speed);
      m2_.run(-speed);
      m3_.run(-speed);
    }
    void obli_r(int speed) {
      m0_.run(0);
      m1_.run(-speed);
      m2_.run(0);
      m3_.run(speed);
    }
    void obli_bl(int speed) {
      m0_.run(0);
      m1_.run(speed);
      m2_.run(0);
      m3_.run(-speed);
    }
    void obli_l(int speed) {
      m0_.run(-speed);
      m1_.run(0);
      m2_.run(speed);
      m3_.run(0);
    }
    void obli_br(int speed) {
      m0_.run(speed);
      m1_.run(0);
      m2_.run(-speed);
      m3_.run(0);
    }
    void stop() {
      m0_.run(0);
      m1_.run(0);
      m2_.run(0);
      m3_.run(0);
    }
};

#endif
