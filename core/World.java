package core;

import commands.Attack;
import commands.Command;
import commands.Drop;
import commands.End;
import commands.Equip;
import commands.Exit;
import commands.GetOff;
import commands.GetOn;
import commands.Help;
import commands.List;
import commands.LookAround;
import commands.Move;
import commands.New;
import commands.PickUp;
import commands.Select;
import commands.Status;
import commands.Steps;
import commands.Tame;
import entities.Amazon;
import entities.Dinoszaurusz;
import items.GepKatana;
import items.Item;
import items.MiniGun;
import items.Pistol;
import items.RocketLauncher;
import items.ShotGun;
import java.io.IOException;
import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;

public class World {
  private Tile[][] tiles;
  
  private HashMap<String, Command> commandMap;
  
  private HashMap<String, Class<?>> itemClassMap;
  
  private HashMap<Boolean, Player> playerMap;
  
  private boolean activePlayer;
  
  private int spawnMax;
  
  private int activeMax;
  
  private int moveCounter;
  
  private int maxCounter;
  
  private int x;
  
  private int y;
  
  public World() {
    Scanner sc = new Scanner(System.in);
    System.out.print("A játékmód száma (jelenleg csak az 1 van): ");
    boolean repeat = true;
    while (repeat) {
      int i;
      Random rand;
      short s;
      String input = sc.nextLine();
      switch (input) {
        case "1":
          System.out.println("Világ létrehozása...");
          this.x = 5;
          this.y = 5;
          this.activeMax = 3;
          this.spawnMax = 6;
          this.maxCounter = 3;
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
          repeat = false;
          continue;
        case "2":
          System.out.println("Nice! Találtál egy hidden feature-t, ami még nem jó!");
          System.out.print("Most írj be egy actual számot, ami van is: ");
          continue;
        case "exit":
          System.exit(0);
          break;
      } 
      System.out.println("Ilyen nincs bruh...\n");
    } 
    this.commandMap = new HashMap<>();
    this.itemClassMap = new HashMap<>();
    this.playerMap = new HashMap<>();
    this.commandMap.put("select", new Select());
    this.commandMap.put("exit", new Exit());
    this.commandMap.put("new", new New());
    this.commandMap.put("help", new Help());
    this.commandMap.put("attack", new Attack());
    this.commandMap.put("move", new Move());
    this.commandMap.put("lookaround", new LookAround());
    this.commandMap.put("tame", new Tame());
    this.commandMap.put("geton", new GetOn());
    this.commandMap.put("getoff", new GetOff());
    this.commandMap.put("status", new Status());
    this.commandMap.put("pickup", new PickUp());
    this.commandMap.put("drop", new Drop());
    this.commandMap.put("equip", new Equip());
    this.commandMap.put("steps", new Steps());
    this.commandMap.put("end", new End());
    this.commandMap.put("list", new List());
    this.itemClassMap.put("pistol", Pistol.class);
    this.itemClassMap.put("katana", GepKatana.class);
    this.itemClassMap.put("shotgun", ShotGun.class);
    this.itemClassMap.put("minigun", MiniGun.class);
    this.itemClassMap.put("rocketlauncher", RocketLauncher.class);
    this.playerMap.put(Boolean.valueOf(true), new Player());
    this.playerMap.put(Boolean.valueOf(false), new Player());
    System.out.println("Világ létrehozva " + this.x + "x" + this.y + " mérettel.");
    System.out.println("A maximális spawnok száma: " + this.spawnMax + ", az egyszerre élö amazonok maximális száma: " + this.activeMax + ".\n");
  }
  
  public void newAmazon(String str) {
    ((Player)getPlayerMap().get(Boolean.valueOf(this.activePlayer))).getAmazonMap().put(str, new Amazon(str));
    if (this.activePlayer) {
      this.tiles[this.x - 1][this.y - 1].addAmazon(((Player)getPlayerMap().get(Boolean.valueOf(this.activePlayer))).getAmazonMap().get(str));
      return;
    } 
    this.tiles[0][0].addAmazon(((Player)getPlayerMap().get(Boolean.valueOf(this.activePlayer))).getAmazonMap().get(str));
  }
  
  public HashMap<String, Command> getCommandMap() {
    return this.commandMap;
  }
  
  public Tile[][] getTiles() {
    return this.tiles;
  }
  
  public HashMap<String, Class<?>> getItemClassMap() {
    return this.itemClassMap;
  }
  
  public HashMap<Boolean, Player> getPlayerMap() {
    return this.playerMap;
  }
  
  public int getX() {
    return this.x;
  }
  
  public int getY() {
    return this.y;
  }
  
  public int getSpawnMax() {
    return this.spawnMax;
  }
  
  public int getActiveMax() {
    return this.activeMax;
  }
  
  public boolean getActivePlayer() {
    return this.activePlayer;
  }
  
  public int getMoveCounter() {
    return this.moveCounter;
  }
  
  public int getMaxCounter() {
    return this.maxCounter;
  }
  
  public void incCounter() {
    this.moveCounter++;
    System.out.println("---Még ennyiszer gyühetsz: " + this.maxCounter - this.moveCounter + "---\n");
  }
  
  public void turn() {
    this.moveCounter = 0;
    ((Select)getCommandMap().get("select")).clearSelection();
    this.activePlayer = !this.activePlayer;
    String os = System.getProperty("os.name");
    try {
      if (os.contains("Windows")) {
        (new ProcessBuilder(new String[] { "cmd", "/c", "cls" })).inheritIO().start().waitFor();
      } else {
        Runtime.getRuntime().exec("clear");
      } 
    } catch (IOException|InterruptedException e) {
      e.printStackTrace();
    } 
  }
}
