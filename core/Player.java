package core;

import entities.Amazon;
import java.util.HashMap;
import java.util.Map;

public class Player {
  private int spawnCounter = 0;
  
  private int activeCounter = 0;
  
  private HashMap<String, Amazon> amazonMap = new HashMap<>();
  
  public int getSpawnCounter() {
    return this.spawnCounter;
  }
  
  public int getActiveCounter() {
    return this.activeCounter;
  }
  
  public HashMap<String, Amazon> getAmazonMap() {
    return this.amazonMap;
  }
  
  public void incActive() {
    this.activeCounter++;
  }
  
  public void decActive() {
    this.activeCounter--;
  }
  
  public void incSpawn() {
    this.spawnCounter++;
  }
  
  public boolean hasAmazon(Amazon a) {
    for (Map.Entry<String, Amazon> entry : this.amazonMap.entrySet()) {
      if (((Amazon)entry.getValue()).equals(a))
        return true; 
    } 
    return false;
  }
}
