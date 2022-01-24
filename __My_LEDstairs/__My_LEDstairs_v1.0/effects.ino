// плавный включатель-выключатель эффектов
void stepFader(bool dir, bool state) {
  // dir 0 на себя, 1 от себя
  // state 0 рост, 1 выкл
  // 0 0
  // 0 1
  // 1 0
  // 1 1
  byte mode = state | (dir << 1);
  byte counter = 0;
  while (1) {
    EVERY_MS(FADR_SPEED) {
      counter++;
      switch (curEffect) {
        case C_WHITE:
          switch (mode) {
            case 0: oneColor(240, 0, 1, 0, counter);  break;            
            case 1: oneColor(240, 0, 1, counter, STEP_AMOUNT); break;
            case 2: oneColor(240, 0, -1, STEP_AMOUNT - counter, STEP_AMOUNT); break;
            case 3: oneColor(240, 0, -1, 0, STEP_AMOUNT - counter); break;
          }
          break;
        case C_AQUA:
          switch (mode) {
            case 0: oneColor(120, 200, 1, 0, counter);  break;            
            case 1: oneColor(120, 200, 1, counter, STEP_AMOUNT); break;
            case 2: oneColor(120, 200, -1, STEP_AMOUNT - counter, STEP_AMOUNT); break;
            case 3: oneColor(120, 200, -1, 0, STEP_AMOUNT - counter); break;
          }
          break;
        case C_VIOLET:
          switch (mode) {
            case 0: oneColor(215, 240, 1, 0, counter);  break;            
            case 1: oneColor(215, 240, 1, counter, STEP_AMOUNT); break;
            case 2: oneColor(215, 240, -1, STEP_AMOUNT - counter, STEP_AMOUNT); break;
            case 3: oneColor(215, 240, -1, 0, STEP_AMOUNT - counter); break;
          }
          break;                    
        case COLOR:
          switch (mode) {
            case 0: staticColor(1, 0, counter); break;
            case 1: staticColor(1, counter, STEP_AMOUNT); break;
            case 2: staticColor(-1, STEP_AMOUNT - counter, STEP_AMOUNT); break;
            case 3: staticColor(-1, 0, STEP_AMOUNT - counter); break;
          }
          break;
        case RAINBOW:
          switch (mode) {
            case 0: rainbowStripes(-1, STEP_AMOUNT - counter, STEP_AMOUNT); break;
            case 1: rainbowStripes(-1, 0, STEP_AMOUNT - counter); break;
            case 2: rainbowStripes(1, STEP_AMOUNT - counter, STEP_AMOUNT); break;
            case 3: rainbowStripes(1, 0, STEP_AMOUNT - counter); break;
          }
          break;
          
      }
      strip.show();
      if (counter == STEP_AMOUNT) break;
    }
  }
  if (state == 1) {
    strip.clear();
    strip.show();
  }
}

// ============== ЭФФЕКТЫ =============
// ========= один цвет
/*
(120,200,255) - AQUA
(215,240,255) - Violet
*/
void oneColor(byte Color, byte Dilution, int8_t dir, byte from, byte to) {
  byte thisBright;
  FOR_i(0, STEP_AMOUNT) {
    thisBright = curBright;     
    if (i < from || i >= to) thisBright = 0;
    fillStep(i, mHSV(Color, Dilution, thisBright));
    //fillStep(i, mCOLOR(ORANGE));
  }
}

// ========= смена цвета общая
void staticColor(int8_t dir, byte from, byte to) {
  byte thisBright;
  static byte colorCounter = 0;
  colorCounter += 2;
  FOR_i(0, STEP_AMOUNT) {
    thisBright = curBright;
    if (i < from || i >= to) thisBright = 0;
    fillStep(i, mHSV(colorCounter, 255, thisBright));
  }
}

// ========= полоски радужные
void rainbowStripes(int8_t dir, byte from, byte to) {
  static byte colorCounter = 0;
  colorCounter += 2;
  byte thisBright;
  FOR_i(0, STEP_AMOUNT) {
    thisBright = curBright;
    if (i < from || i >= to) thisBright = 0;
    fillStep((dir > 0) ? (i) : (STEP_AMOUNT - 1 - i), mHSV(colorCounter + (float)i * 255 / STEP_AMOUNT, 255, thisBright));
  }
}

// ========= залить ступеньку цветом (служебное)
void fillStep(int8_t num, LEDdata color) {
  if (num >= STEP_AMOUNT || num < 0) return;
  FOR_i(num * STEP_LENGTH, num * STEP_LENGTH + STEP_LENGTH) {
    leds[i] = color;
  }
}

