public class GameObject {

    public float x;
    public float y;
    public final float w;
    public final float h;

    int speed = 1;

    enum types {
        player1,
        player2,
        wall,
        point1,
        point2
    }

    final types t;


    public GameObject(types t, float x, float y, float w, float h) {
        this.t = t;
        this.x = x;
        this.y = y;
        this.w = w;
        this.h = h;
    }





}
