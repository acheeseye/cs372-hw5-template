// shape.h
// Project: CPS
// Base class Shape 

#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <vector>
#include <memory>

#include <initializer_list>

class Shape 
{
public:

    Shape(double width, double height);
    virtual ~Shape() = default;

    virtual std::string to_postscript() const = 0;
	void generate_postscript_file(const std::string & file_name) const;
	std::string g_save() const;
	std::string g_restore() const;

	double get_width() const;
	double get_height() const;
	double get_xpos() const;
	double get_ypos() const;

	void set_width(double width);
	void set_height(double height);
	void set_xpos(double x);
	void set_ypos(double y);

private:

    double m_width;
    double m_height;
	double m_xpos;
	double m_ypos;
};

class Compound : public Shape
{
public:
	using ShapeCollection = std::vector<std::shared_ptr<Shape>>;

	explicit Compound(const ShapeCollection & shapes);
	virtual ~Compound() = default;
	virtual std::string translate(int index) const = 0;
	virtual void generate_translate_points() = 0;

	std::string to_postscript() const override;
	ShapeCollection get_shapes() const;

protected:

	ShapeCollection m_shapes;
	std::vector<double> m_translate_points;
};

class CompoundLayered : public Compound
{
public:
	explicit CompoundLayered(const ShapeCollection & shapes);
	~CompoundLayered() = default;
	std::string translate(int nil) const override;
	void generate_translate_points() override;
};

class CompoundVertical : public Compound
{
public:
	explicit CompoundVertical(const ShapeCollection & shapes);
	~CompoundVertical() = default;
	std::string translate(int index) const override;
	void generate_translate_points() override;
};

class CompoundHorizontal : public Compound
{
public:
	explicit CompoundHorizontal(const ShapeCollection & shapes);
	~CompoundHorizontal() = default;
	std::string translate(int index) const override;
	void generate_translate_points() override;
};

class Circle: public Shape
{
public:
	Circle() = default;
	Circle(double radius);
	~Circle() = default;
	std::string to_postscript() const;
private:
	double m_radius;
};

class Polygon : public Shape
{
public:
	Polygon() = default;
	Polygon(int num_sides, double side_length);
	virtual ~Polygon() = default;
	std::string to_postscript() const;
private:
	int m_num_sides;
	double m_side_length;
};

class Rectangle : public Shape
{
public:
	Rectangle() = default;
	Rectangle(double width, double height): Shape(width, height){}
	~Rectangle() = default;
	std::string to_postscript() const;
private:
};

class Spacer : public Shape
{
public:
	Spacer() = default;
	Spacer(double width, double height): Shape(width, height){}
	~Spacer() = default;
	std::string to_postscript() const;
private:
};

class Square : public Polygon
{
public:
	Square() = default;
	Square(double side_length): Polygon(4, side_length){}
	~Square() = default;
private:
};

class Triangle : public Polygon
{
public:
	Triangle() = default;
	Triangle(double side_length): Polygon(3, side_length){}
	~Triangle() = default;
private:
};

class Rotated : public Shape
{
public:
	enum RotationAngle { QUARTER = 90, HALF = 180, THREE_QUARTER = 270 };
	Rotated() = default;
	Rotated(std::shared_ptr<Shape> shape, RotationAngle rotation_angle);
	~Rotated() = default;
	std::string to_postscript() const;
private:
	RotationAngle m_rot;
	std::shared_ptr<Shape> m_shape;
};

class Scaled : public Shape
{
public:
	Scaled() = default;
	Scaled(std::shared_ptr<Shape> shape, double fx, double fy);
	~Scaled() = default;
	std::string to_postscript() const;
private:
	std::shared_ptr<Shape> m_shape;
	double m_fx;
	double m_fy;
};

class Layered : public Shape
{
public:
	Layered() = default;
	Layered(std::initializer_list<std::shared_ptr<Shape>> shapes);
	~Layered() = default;
	std::string to_postscript() const;
private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
};

class Vertical : public Shape
{
public:
	Vertical() = default;
	Vertical(std::initializer_list<std::shared_ptr<Shape>> shapes);
	~Vertical() = default;
	std::string to_postscript() const;
private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
};

class Horizontal : public Shape
{
public:
	Horizontal() = default;
	Horizontal(std::initializer_list<std::shared_ptr<Shape>> shapes);
	~Horizontal() = default;
	std::string to_postscript() const;
private:
	std::vector<std::shared_ptr<Shape>> m_shapes;
};

class Diamond : public Shape
{
public:
	Diamond() = default;
	Diamond(double side_length);
	~Diamond() = default;
	std::string to_postscript() const;
private:
};

class STriangle : public Shape
{
public:
	STriangle() = default;
	STriangle(double side, int depth);
	~STriangle() = default;
	std::string to_postscript() const;
private:
	std::vector < std::shared_ptr<Shape>> m_subTriangles;
};

class U_Curve: public Shape
{
public:
	U_Curve() = default;
	U_Curve(double side):Shape(side, side){}
	~U_Curve() = default;
	std::string to_postscript() const;
private:
	std::vector<std::shared_ptr<Shape>> m_subLPB;
};
//Line plane bijection
class LPB : public Shape
{
public:
	LPB() = default;
	LPB(double side, int depth);
	~LPB() = default;
	std::string to_postscript() const;
private:
	std::vector<std::shared_ptr<Shape>> m_subLPB;
	int m_depth;
};

#endif // SHAPE_HPP
