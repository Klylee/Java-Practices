package mypackage;

public class Triangle extends Graph {
    private Vec2d vertex1;
    private Vec2d vertex2;
    private Vec2d vertex3;

    public Triangle() {
        super();
        vertex1 = new Vec2d();
        vertex2 = new Vec2d();
        vertex3 = new Vec2d();
    }

    public Triangle(GraphType type, String name, Vec2d pos, Vec2d ver1, Vec2d ver2, Vec2d ver3, Color color) {
        super(type, name, pos, color);
        vertex1 = ver1;
        vertex2 = ver2;
        vertex3 = ver3;
    }

    public Vec2d v1() {
        return vertex1;
    }

    public Vec2d v2() {
        return vertex2;
    }

    public Vec2d v3() {
        return vertex3;
    }

    public float area() {
        Vec2d a = new Vec2d(vertex2.x() - vertex1.x(), vertex2.y() - vertex1.y());
        Vec2d b = new Vec2d(vertex3.x() - vertex1.x(), vertex3.y() - vertex1.y());
        Vec2d a_norm = new Vec2d(a);
        a_norm.normalize();
        float b_cast = a_norm.x() * b.x() + a_norm.y() * b.y();
        float h = (float) Math.sqrt(b.x() * b.x() + b.y() * b.y() - b_cast * b_cast);

        return 0.5f * h * a.mod();
    }
}
