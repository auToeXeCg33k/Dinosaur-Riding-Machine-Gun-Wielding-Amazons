package core;

import entities.Dinoszaurusz;
import items.GepKatana;
import items.Item;
import items.MiniGun;
import items.Pistol;
import items.ShotGun;
import java.util.Random;

public class World {
  private Tile[][] tiles;
  
  private int size;
  
  public World(byte n) {
    int i;
    Random rand;
    short s;
    int j;
    switch (n) {
      case 1:
        this.size = 5;
        this.tiles = new Tile[5][5];
        for (i = 0; i < 5; i++) {
          for (int k = 0; k < 5; k++)
            this.tiles[i][k] = new Tile(); 
        } 
        rand = new Random();
        for (s = 0; s < 6; s = (short)(s + 1))
          while (!this.tiles[rand.nextInt(4)][rand.nextInt(4)].spawn(new Dinoszaurusz())); 
        for (j = 0; j < 2; j++)
          while (!this.tiles[4][rand.nextInt(4)].spawn((Item)new Pistol())); 
        for (j = 0; j < 2; j++)
          while (!this.tiles[0][rand.nextInt(4)].spawn((Item)new Pistol())); 
        while (!this.tiles[rand.nextInt(1)][rand.nextInt(4)].spawn((Item)new ShotGun()));
        while (!this.tiles[4 - rand.nextInt(1)][rand.nextInt(4)].spawn((Item)new ShotGun()));
        while (!this.tiles[rand.nextInt(4)][rand.nextInt(4)].spawn((Item)new GepKatana()));
        while (!this.tiles[2][rand.nextInt(4)].spawn((Item)new MiniGun()));
        for (j = 0; j < 2; j++)
          while (!this.tiles[3 - rand.nextInt(2)][rand.nextInt(4)].spawn()); 
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
