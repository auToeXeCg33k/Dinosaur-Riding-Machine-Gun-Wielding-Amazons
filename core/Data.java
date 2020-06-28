package core;

import commands.Command;
import commands.Select;

public class Data {
  private boolean playerMarker = false;
  
  private World world;
  
  private Maps maps = new Maps();
  
  private Counters counters = new Counters();
  
  public boolean getPlayerMarker() {
    return this.playerMarker;
  }
  
  public World getWorld() {
    return this.world;
  }
  
  public Maps getMaps() {
    return this.maps;
  }
  
  public Counters getCounters() {
    return this.counters;
  }
  
  public Player getActivePlayer() {
    return this.maps.getPlayerMap().get(Boolean.valueOf(this.playerMarker));
  }
  
  public Player getOtherPlayer() {
    return this.maps.getPlayerMap().get(Boolean.valueOf(!this.playerMarker));
  }
  
  public Command getCommand(String name) {
    if (getMaps().getCommandMap().containsKey(name))
      return getMaps().getCommandMap().get(name); 
    return null;
  }
  
  public String newAmazon(String name) {
    ((Player)this.maps.getPlayerMap().get(Boolean.valueOf(this.playerMarker))).addAmazon(name);
    if (this.playerMarker) {
      this.world.getTiles()[this.world.getSize().getX() - 1][this.world.getSize().getY() - 1].addAmazon(getActivePlayer().getAmazon(name));
    } else {
      this.world.getTiles()[0][0].addAmazon(getActivePlayer().getAmazon(name));
    } 
    return name + " létrehozva az 1;1 mezőn.\n";
  }
  
  public void turn() {
    this.counters.nullMoves();
    ((Select)this.maps.getCommandMap().get("select")).clearSelection();
    this.playerMarker = !this.playerMarker;
  }
  
  public void incSpawn() {
    getActivePlayer().incSpawn();
  }
  
  public void incActive() {
    getActivePlayer().incActive();
  }
  
  public String nextMove() {
    return this.counters.nextMove();
  }
  
  public boolean canDoAction() {
    return (this.counters.getMaxMoves() > this.counters.getMoves());
  }
  
  public Tile tileOfSelected() {
    for (int i = 0; i < (this.world.getTiles()).length; i++) {
      for (int j = 0; j < (this.world.getTiles()[0]).length; j++) {
        if (this.world.getTiles()[i][j].containsAmazon(((Select)getCommand("select")).getSelection()))
          return this.world.getTiles()[i][j]; 
      } 
    } 
    return null;
  }
  
  public String createWorld(byte n) {
    if (this.world == null) {
      this.world = new World(n);
      int active = 0;
      int moves = 0;
      int spawn = 0;
      int size = 0;
      String ret = "Világ létrehozása...\nVilág létrehozva ";
      switch (n) {
        case 1:
          active = 3;
          moves = 3;
          spawn = 6;
          size = 5;
          break;
      } 
      this.counters.setMaxActive(active);
      this.counters.setMaxMoves(moves);
      this.counters.setMaxSpawn(spawn);
      return ret.concat("" + size + "x" + size + " mérettel.\nA maximális spawnok száma: " + size + ", a játékosonként egyszerre élő amazonok maximális száma: " + spawn + ".\n");
    } 
    return "";
  }
}
