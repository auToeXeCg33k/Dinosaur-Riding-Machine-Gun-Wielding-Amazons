package core;

import commands.Attack;
import commands.Command;
import commands.Drop;
import commands.End;
import commands.Equip;
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
import items.GepKatana;
import items.MiniGun;
import items.Pistol;
import items.RocketLauncher;
import items.ShotGun;
import java.util.HashMap;

public class Data {
  private final HashMap<String, Command> commands;
  
  private final HashMap<String, Class<?>> items;
  
  private final HashMap<Boolean, Player> players;
  
  private World world;
  
  private boolean playerMarker;
  
  private int moves;
  
  private int maxMoves;
  
  private int maxSpawn;
  
  private int maxActive;
  
  public Data() {
    this.playerMarker = false;
    this.commands = new HashMap<>();
    this.commands.put("select", new Select());
    this.commands.put("new", new New());
    this.commands.put("help", new Help());
    this.commands.put("attack", new Attack());
    this.commands.put("move", new Move());
    this.commands.put("lookaround", new LookAround());
    this.commands.put("tame", new Tame());
    this.commands.put("geton", new GetOn());
    this.commands.put("getoff", new GetOff());
    this.commands.put("status", new Status());
    this.commands.put("pickup", new PickUp());
    this.commands.put("drop", new Drop());
    this.commands.put("equip", new Equip());
    this.commands.put("steps", new Steps());
    this.commands.put("list", new List());
    this.commands.put("end", new End());
    this.items = new HashMap<>();
    this.items.put("pisztoly", Pistol.class);
    this.items.put("gépkatana", GepKatana.class);
    this.items.put("shotgun", ShotGun.class);
    this.items.put("minigun", MiniGun.class);
    this.items.put("rocketlauncher", RocketLauncher.class);
    this.players = new HashMap<>();
    this.players.put(Boolean.valueOf(true), new Player());
    this.players.put(Boolean.valueOf(false), new Player());
    this.moves = 0;
  }
  
  public boolean getPlayerMarker() {
    return this.playerMarker;
  }
  
  public int getMoves() {
    return this.moves;
  }
  
  public int getMaxMoves() {
    return this.maxMoves;
  }
  
  public int getMaxSpawn() {
    return this.maxSpawn;
  }
  
  public int getMaxActive() {
    return this.maxActive;
  }
  
  public World getWorld() {
    return this.world;
  }
  
  public HashMap<String, Command> getCommands() {
    return this.commands;
  }
  
  public HashMap<Boolean, Player> getPlayers() {
    return this.players;
  }
  
  public HashMap<String, Class<?>> getItems() {
    return this.items;
  }
  
  public Report startGame(byte n) {
    switch (n) {
      case 1:
        this.world = new World(n);
        this.maxActive = 3;
        this.maxMoves = 3;
        this.maxSpawn = 6;
        return new Report("Világ létrehozva " + this.world.getSize() + "x" + this.world.getSize() + " mérettel.\nA maximális spawnok száma: " + this.maxSpawn + ", a játékosonként egyszerre élő amazonok maximális száma: " + this.maxActive + ".\n", true);
    } 
    return new Report("Ilyen játékmód nincs is. Retry: ", false);
  }
  
  public String nextMove() {
    this.moves++;
    return "\n---Még ennyiszer gyühetsz: " + this.maxMoves - this.moves + "---\n";
  }
  
  public void turn() {
    this.moves = 0;
    ((Select)this.commands.get("select")).clearSelection();
    this.playerMarker = !this.playerMarker;
  }
  
  public String newAmazon(String name) {
    ((Player)this.players.get(Boolean.valueOf(this.playerMarker))).addAmazon(name);
    if (this.playerMarker) {
      this.world.getTiles()[this.world.getSize() - 1][this.world.getSize() - 1].add(((Player)this.players.get(Boolean.valueOf(this.playerMarker))).getAmazon(name));
    } else {
      this.world.getTiles()[0][0].add(((Player)this.players.get(Boolean.valueOf(this.playerMarker))).getAmazon(name));
    } 
    return name + " létrehozva az 1;1 mezőn.\n";
  }
  
  public Tile tileOfSelected() {
    for (int i = 0; i < (this.world.getTiles()).length; i++) {
      for (int j = 0; j < (this.world.getTiles()[0]).length; j++) {
        if (this.world.getTiles()[i][j].contains(((Select)this.commands.get("select")).getSelection()))
          return this.world.getTiles()[i][j]; 
      } 
    } 
    return null;
  }
}
