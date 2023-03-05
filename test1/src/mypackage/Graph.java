package mypackage;

public abstract class Graph {
    private GraphType type;
    private String name;
    private Color color;
    private Vec2d position;

    public Graph() {
        this.type = GraphType.NONETYPE;
        this.color = new Color();
        this.position = new Vec2d();
    }

    public Graph(GraphType type, String name, Vec2d pos, Color color) {
        this.type = type;
        this.name = name;
        this.position = pos;
        this.color = color;
    }

    public GraphType getType() {
        return type;
    }

    public String getName() {
        return this.name;
    }

    public Color color() {
        return this.color;
    }

    public Vec2d position() {
        return this.position;
    }

    public abstract float area();
}