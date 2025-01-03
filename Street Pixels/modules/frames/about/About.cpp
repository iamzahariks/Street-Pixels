#include "AboutHeader.h"
#include "../../music/hmusic.h"
#include "objsContainer/AC_Header.h"
#include "../../other/keyboard/KeyboardHeader.h"

// ������ ����
bool mouseButton = false;
void About_Render(sf::RenderWindow &window, int fps) {
	AboutContainer *container = GetContainer();
	container->fpsText.setString(std::to_string(fps));

	// ������
	window.draw(container->backgroundSprite_about);
	window.draw(container->fpsText);

	// ������� �� ������
	if ((window.hasFocus()) && (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (!mouseButton)) {
		mouseButton = true;
	}
	else {
		if ((!sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (mouseButton)) {
			mouseButton = false;
		}
	}
}

// ���� �����������
void About_Closing() {
	mouseButton = false;
}

// ������� ���������� � ���
void About_Leave(sf::RenderWindow& window) {
	MusicContainer* music = GetMusic();
	music->aboutSound.play();
	OpenFrame("menu");
};

Frame _createdAbout;
Frame* GetAbout() {
	if (_createdAbout.frameName == "frame") {
		_createdAbout.frameName = "about";

		_createdAbout.Render = About_Render;
		_createdAbout.Closing = About_Closing;

		KeyPressConnect(sf::Keyboard::Escape, "about", About_Leave);
	}

	return &_createdAbout;
}