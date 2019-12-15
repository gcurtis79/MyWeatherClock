uint8_t display_mode = 0;

void button_init()
{
  pinMode(BUTTON, INPUT_PULLUP);
}

void button_loop()
{
  if (digitalRead(BUTTON) == LOW)
  {
    display_mode++;
    while (digitalRead(BUTTON) == LOW)
      display.clearDisplay();
  }
}