import java.util.*;

abstract class Game {

    ArrayList<GameObject> gameObjectArrayList = new ArrayList<>();

    GameObject player1obj;
    GameObject player2obj;

    public Game() {
        player1obj = new GameObject(GameObject.types.player1, 84,384,32,32);
        player2obj = new GameObject(GameObject.types.player2, 1164, 384, 32,32);

        gameObjectArrayList.add(player1obj);
        gameObjectArrayList.add(player2obj);
    }

    public void update(Inputs inputs) {
        if (inputs.keydowns1[inputs.keyW]) {
            player1obj.y -= player1obj.speed;
        }
        if (inputs.keydowns1[inputs.keyA]) {
            player1obj.x -= player1obj.speed;
        }
        if (inputs.keydowns1[inputs.keyS]) {
            player1obj.y += player1obj.speed;
        }
        if (inputs.keydowns1[inputs.keyD]) {
            player1obj.x += player1obj.speed;
        }
        if (inputs.keydowns2[inputs.keyW]) {
            player2obj.y -= player2obj.speed;
        }
        if (inputs.keydowns2[inputs.keyA]) {
            player2obj.x -= player2obj.speed;
        }
        if (inputs.keydowns2[inputs.keyS]) {
            player2obj.y += player2obj.speed;
        }
        if (inputs.keydowns2[inputs.keyD]) {
            player2obj.x += player2obj.speed;
        }

    }
}
