void button_init()
{
  pinMode(BUTTON, INPUT_PULLUP);
}

void button_loop()
{
  if (digitalRead(BUTTON) == LOW)
    while (digitalRead(BUTTON) == LOW)
      display_IP();
}