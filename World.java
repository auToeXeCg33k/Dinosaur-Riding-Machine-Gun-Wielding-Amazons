import java.util.HashMap;
import java.util.Map;

public class World {
  Tile[][] tiles;
  
  private Map<String, Dinoszaurusz> dinoszauruszMap;
  
  private Map<String, Amazon> amazonMap;
  
  private Map<String, Command> commandMap;
  
  public World(int x, int y) {
    this.tiles = new Tile[x][y];
    for (int i = 0; i < x; i++) {
      for (int j = 0; j < y; j++)
        this.tiles[i][j] = new Tile(); 
    } 
    this.dinoszauruszMap = new HashMap<>();
    this.amazonMap = new HashMap<>();
    this.commandMap = new HashMap<>();
    this.commandMap.put("select", new Select());
    this.commandMap.put("exit", new Exit());
    this.commandMap.put("new", new New());
    this.commandMap.put("help", new Help());
    this.commandMap.put("attack", new Attack());
    this.commandMap.put("where", new Where());
  }
  
  public void newDinoszaurusz(String str) {
    this.dinoszauruszMap.put(str, new Dinoszaurusz(str));
    this.tiles[0][0].addDinoszaurusz(this.dinoszauruszMap.get(str));
  }
  
  public void newAmazon(String str) {
    this.amazonMap.put(str, new Amazon(str, true, true, true));
    this.tiles[0][0].addAmazon(this.amazonMap.get(str));
  }
  
  public Map<String, Amazon> getAmazonMap() {
    return this.amazonMap;
  }
  
  public Map<String, Dinoszaurusz> getDinoszauruszMap() {
    return this.dinoszauruszMap;
  }
  
  public Map<String, Command> getCommandMap() {
    return this.commandMap;
  }
  
  public Tile[][] getTiles() {
    return this.tiles;
  }
}
