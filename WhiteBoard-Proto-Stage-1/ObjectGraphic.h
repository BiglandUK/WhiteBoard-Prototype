// ObjectGraphic.h

enum class GraphicType{Group=0, Vector, Image, Text};


// Base class for visual depictions of objects.
class ObjectGraphic{
public:
  ObjectGraphic(GraphicType gType);
  
  GraphicType GetType()const;
  
  void Render() = 0;
};
