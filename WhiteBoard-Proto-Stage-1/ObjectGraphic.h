// ObjectGraphic.h
#include "SFML/Graphics.hpp"
#include "Object.h"
#include <string>

enum class GraphicType{Group=0, Vector, Image, Text};

// Base class for visual depictions of objects.
class ObjectGraphic{
public:  
  virtual GraphicType	GetType() const = 0;
  virtual void			Render(Object& object, sf::RenderWindow& window) = 0;

};

// Circle objects
class VectorCircle : public ObjectGraphic{
public:
  VectorCircle(float radius, const sf::Color& colour);
  
  GraphicType GetType() const;
  void Render(Object& object, sf::RenderWindow& window);
  
  float GetRadius()const;
  void SetRadius(float radius);
  
  sf::Color GetColour() const;
  void SetColour(const sf::Color& colour);
  
  private:
      float mRadius;
      sf::Color mFillColour;
};

// Currently only rectangules
class VectorPolygon : public ObjectGraphic{
 public:  
  VectorPolygon(float width, float height, const sf::Color colour);
  GraphicType GetType() const;
  void Render(Object& object, sf::RenderWindow& window);
  
  private:
  sf::Color mFillColour;
  float mWidth, mHeight;
};

class TextGraphic : public ObjectGraphic {
public:
	TextGraphic(std::string text);
	GraphicType GetType() const;
	void Render(Object& object, sf::RenderWindow& window);

private:
	std::string mText;
};
