package core;

import entities.Dinoszaurusz;
import items.*;


public class World {
    private Tile[][] tiles;
    private int size;


    public World(byte n) {
        switch (n) {
            case 1:
                this.size = 5;
                this.tiles = new Tile[5][5];
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++)
                        this.tiles[i][j] = new Tile();

                java.util.Random rand = new java.util.Random();
                for (short i = 0; i < 6; i++)
                    while (!tiles[rand.nextInt(4)][rand.nextInt(4)].spawn(new Dinoszaurusz())) ;

                for (int i = 0; i < 2; i++)
                    while (!tiles[4][rand.nextInt(4)].spawn(new Pistol())) ;

                for (int i = 0; i < 2; i++)
                    while (!tiles[0][rand.nextInt(4)].spawn(new Pistol())) ;

                while (!tiles[rand.nextInt(1)][rand.nextInt(4)].spawn(new ShotGun())) ;
                while (!tiles[4 - rand.nextInt(1)][rand.nextInt(4)].spawn(new ShotGun())) ;
                while (!tiles[rand.nextInt(4)][rand.nextInt(4)].spawn(new GepKatana())) ;
                while (!tiles[2][rand.nextInt(4)].spawn(new MiniGun())) ;

                for (int i = 0; i < 2;i++)
                    while(!tiles[3 - rand.nextInt(2)][rand.nextInt(4)].spawn());
                break;
        }
    }


    public Tile[][] getTiles() {
        return this.tiles;
    }
    public int getSize() {
        return this.size;
    }
}
