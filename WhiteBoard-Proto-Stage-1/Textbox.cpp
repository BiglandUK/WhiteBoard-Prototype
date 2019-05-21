#include "Textbox.h"

Textbox::Textbox() {
	Setup(5, 9, 200, sf::Vector2f(0, 0));
}

Textbox::Textbox(int visible, int charSize, int width, sf::Vector2f screenPos) {
	Setup(visible, charSize, width, screenPos);
}

Textbox::~Textbox() {
	Clear();
}

void Textbox::Setup(int visible, int charSize, int width, sf::Vector2f screenPos) {
	numVisible_ = visible;

	sf::Vector2f offset(2.0f, 2.0f);
	font_.loadFromFile("arial.ttf");
	content_.setFont(font_);
	content_.setString("");
	content_.setCharacterSize(charSize);
	content_.setFillColor(sf::Color::White);
	content_.setPosition(screenPos + offset);

	backdrop_.setSize(sf::Vector2f(width, (visible* (charSize* 1.2f))));
	backdrop_.setFillColor(sf::Color(90, 90, 90, 90));
	backdrop_.setPosition(screenPos);
}

void Textbox::Add(std::string message) {
	messages_.push_back(message);
	if (messages_.size() < 6) { return; }
	messages_.erase(messages_.begin());
}

void Textbox::Clear() { messages_.clear(); }

void Textbox::Render(sf::RenderWindow& window) {
	std::string content;
	for (auto &itr : messages_) {
		content.append(itr + "\n");
	}

	if (content != "") {
		content_.setString(content);
		window.draw(backdrop_);
		window.draw(content_);
	}
}