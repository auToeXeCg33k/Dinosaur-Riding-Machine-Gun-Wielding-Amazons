package core;

public class Counters {
  private int moves = 0;
  
  private int MaxMoves;
  
  private int maxSpawn;
  
  private int maxActive;
  
  public int getMoves() {
    return this.moves;
  }
  
  public int getMaxMoves() {
    return this.MaxMoves;
  }
  
  public int getMaxSpawn() {
    return this.maxSpawn;
  }
  
  public int getMaxActive() {
    return this.maxActive;
  }
  
  public void setMaxMoves(int maxMoves) {
    this.MaxMoves = maxMoves;
  }
  
  public void setMaxSpawn(int maxSpawn) {
    this.maxSpawn = maxSpawn;
  }
  
  public void setMaxActive(int maxActive) {
    this.maxActive = maxActive;
  }
  
  public void nullMoves() {
    this.moves = 0;
  }
  
  public String nextMove() {
    this.moves++;
    return "\n---Még ennyiszer gyühetsz: " + this.MaxMoves - this.moves + "---\n";
  }
}
