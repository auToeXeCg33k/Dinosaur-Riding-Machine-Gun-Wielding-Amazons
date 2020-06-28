import java.util.HashMap;

public class World {
  Tile[][] tiles;
  
  private HashMap<String, Dinoszaurusz> dinoszauruszMap;
  
  private HashMap<String, Amazon> amazonMap;
  
  private HashMap<String, Command> commandMap;
  
  int x;
  
  int y;
  
  public World(int x, int y) {
    this.x = x;
    this.y = y;
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
    this.commandMap.put("move", new Move());
    this.commandMap.put("lookaround", new LookAround());
  }
  
  public void newDinoszaurusz(String str) {
    this.dinoszauruszMap.put(str, new Dinoszaurusz(str));
    this.tiles[0][0].addDinoszaurusz(this.dinoszauruszMap.get(str));
  }
  
  public void newAmazon(String str) {
    this.amazonMap.put(str, new Amazon(str, true, true, true));
    this.tiles[0][0].addAmazon(this.amazonMap.get(str));
  }
  
  public HashMap<String, Amazon> getAmazonMap() {
    return this.amazonMap;
  }
  
  public HashMap<String, Dinoszaurusz> getDinoszauruszMap() {
    return this.dinoszauruszMap;
  }
  
  public HashMap<String, Command> getCommandMap() {
    return this.commandMap;
  }
  
  public Tile[][] getTiles() {
    return this.tiles;
  }
  
  public int getX() {
    return this.x;
  }
  
  public int getY() {
    return this.y;
  }
}
