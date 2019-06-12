// ObjectGraphic.h

enum class GraphicType{Group=0, Vector, Image, Text};


// Base class for visual depictions of objects.
class ObjectGraphic{
public:
  ObjectGraphic(GraphicType gType);
  
  GraphicType GetType()const;
  
  void Render(const Object& object, sf::RenderWindow& window) = 0;
};

class VectorCircle : public ObjectGraphic{
public:
  VectorCircle(float radius, const sf::Color& colour);
  
  void Render(const Object& object, sf::RenderWindow& window);
  
  float GetRadius()const;
  void SetRadius(float radius);
  
  sf::Color GetColour() const;
  void SetColour(const sf::Color& colour);
  
  private:
      float mRadius;
      sf::Color mFillColour;
};

class VectorPolygon : public ObjectGraphic{
 public:
  VectorPolygon();
  
  void Render(const Object& object, sf::RenderWindow& window);
  
  private:
  sf::Color mFillColour;
};
