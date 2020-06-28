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
  
  private Size size;
  
  public World(byte n) {
    int i;
    Random rand;
    short s;
    switch (n) {
      case 1:
        this.size = new Size(5, 5);
        this.tiles = new Tile[5][5];
        for (i = 0; i < 5; i++) {
          for (int j = 0; j < 5; j++)
            this.tiles[i][j] = new Tile(); 
        } 
        rand = new Random();
        while (!this.tiles[2][rand.nextInt(4)].spawnItem((Item)new MiniGun()));
        while (!this.tiles[rand.nextInt(4)][rand.nextInt(4)].spawnItem((Item)new GepKatana()));
        while (!this.tiles[rand.nextInt(1)][rand.nextInt(4)].spawnItem((Item)new ShotGun()));
        while (!this.tiles[4 - rand.nextInt(1)][rand.nextInt(4)].spawnItem((Item)new ShotGun()));
        while (!this.tiles[0][rand.nextInt(4)].spawnItem((Item)new Pistol()));
        while (!this.tiles[0][rand.nextInt(4)].spawnItem((Item)new Pistol()));
        while (!this.tiles[4][rand.nextInt(4)].spawnItem((Item)new Pistol()));
        while (!this.tiles[4][rand.nextInt(4)].spawnItem((Item)new Pistol()));
        for (s = 0; s < 6; s = (short)(s + 1))
          while (!this.tiles[rand.nextInt(4)][rand.nextInt(4)].spawnDinoszaurusz(new Dinoszaurusz())); 
        break;
    } 
  }
  
  public Tile[][] getTiles() {
    return this.tiles;
  }
  
  public Size getSize() {
    return this.size;
  }
}
