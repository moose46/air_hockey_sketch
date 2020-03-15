int ResetBtnCurrentState = 0;
int Player1BtnCurrentState = 0;
int buttonPlayer2CurrentState = 0;
int Player1Score = 0;
int Player2Score = 0;
void processResetBtnState(int readingResetButton)
{

	// if the button state has changed:
	if (readingResetButton != ResetBtnCurrentState) {
		ResetBtnCurrentState = readingResetButton;

		// only toggle the LED if the new button state is HIGH
		if (ResetBtnCurrentState == HIGH) {
			ledState = !ledState;
			//scoreBoard += 100;
			Player1Score = 0;
			Player2Score = 0;
			scoreBoard = 0;
			sevseg.setNumber(scoreBoard, 2);
		}
	}

}
void processPlayer1BtnState(int readingPlayer1Button)
{

	// if the button state has changed:
	if (readingPlayer1Button != Player1BtnCurrentState) {
		Player1BtnCurrentState = readingPlayer1Button;

		// only toggle the LED if the new button state is HIGH
		if (Player1BtnCurrentState == HIGH) {
			ledState = !ledState;
			if (Player1Score < 15)
				Player1Score += 1;
			scoreBoard = Player1Score * 100 + Player2Score;
			sevseg.setNumber(scoreBoard, 2);
		}
	}

}
void processPlayer2BtnState(int readingPlayer2Button)
{

	// if the button state has changed:
	if (readingPlayer2Button != buttonPlayer2CurrentState) {
		buttonPlayer2CurrentState = readingPlayer2Button;

		// only toggle the LED if the new button state is HIGH
		if (buttonPlayer2CurrentState == HIGH) {
			ledState = !ledState;
			if (Player2Score < 15)
				Player2Score += 1;
			scoreBoard = Player1Score * 100 + Player2Score;
			sevseg.setNumber(scoreBoard, 2);
		}
	}

}
