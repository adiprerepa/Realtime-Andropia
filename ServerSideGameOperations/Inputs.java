abstract class Inputs {

    static int keyW = 0;
    static int keyA = 1;
    static int keyS = 2;
    static int keyD = 3;

    public boolean[] keydowns1 = new boolean[4];
    public boolean[] keydowns2 = new boolean[4];

    void pressKey(int player, int key) {
        if (player == 1) {
            keydowns1[key] = true;
        }
        if (player == 2) {
            keydowns2[key] = true;
        }
    }

    void releaseKey(int player, int key) {
        if (player == 1) {
            keydowns1[key] = false;
        }
        if (player == 2) {
            keydowns2[key] = false;
        }
    }

}
