import java.util.HashMap;
import java.util.Random;
import java.util.Scanner;

public class World {
  private int spawnMax;
  
  private int activeMax;
  
  private Tile[][] tiles;
  
  private HashMap<String, Amazon> amazonMap;
  
  private HashMap<String, Command> commandMap;
  
  private int x;
  
  private int y;
  
  private HashMap<String, Class<?>> itemClassMap;
  
  public World() {
    Scanner sc = new Scanner(System.in);
    System.out.println("add meg a gecit (jelenleg csak a geci1 érhető el):");
    boolean repeat = true;
    while (repeat) {
      String input = sc.nextLine();
      String[] dimenziok = input.split(" ");
      if (dimenziok.length == 1) {
        int i;
        Random rand;
        short s;
        System.out.println("initializing world");
        switch (dimenziok[0]) {
          case "geci1":
            this.x = 5;
            this.y = 5;
            this.activeMax = 3;
            this.spawnMax = 10;
            this.tiles = new Tile[5][5];
            for (i = 0; i < 5; i++) {
              for (int j = 0; j < 5; j++)
                this.tiles[i][j] = new Tile(); 
            } 
            rand = new Random();
            while (!this.tiles[2][rand.nextInt(4)].spawnItem(new MiniGun()));
            while (!this.tiles[rand.nextInt(4)][rand.nextInt(4)].spawnItem(new GepKatana()));
            while (!this.tiles[rand.nextInt(1)][rand.nextInt(4)].spawnItem(new ShotGun()));
            while (!this.tiles[4 - rand.nextInt(1)][rand.nextInt(4)].spawnItem(new ShotGun()));
            while (!this.tiles[0][rand.nextInt(4)].spawnItem(new Pistol()));
            while (!this.tiles[0][rand.nextInt(4)].spawnItem(new Pistol()));
            while (!this.tiles[4][rand.nextInt(4)].spawnItem(new Pistol()));
            while (!this.tiles[4][rand.nextInt(4)].spawnItem(new Pistol()));
            for (s = 0; s < 6; s = (short)(s + 1))
              while (!this.tiles[rand.nextInt(4)][rand.nextInt(4)].spawnDinoszaurusz(new Dinoszaurusz())); 
            repeat = false;
            continue;
          case "geci2":
            System.out.println("hidden feature - ez még nem ready");
            continue;
        } 
        System.out.println("ilyen nincs bruh");
        continue;
      } 
      System.out.println("ez túl sok faszság");
    } 
    this.amazonMap = new HashMap<>();
    this.commandMap = new HashMap<>();
    this.itemClassMap = new HashMap<>();
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
    this.itemClassMap.put("pistol", Pistol.class);
    this.itemClassMap.put("katana", GepKatana.class);
    this.itemClassMap.put("shotgun", ShotGun.class);
    this.itemClassMap.put("minigun", MiniGun.class);
    this.itemClassMap.put("rocketlauncher", RocketLauncher.class);
    System.out.println("world initialized");
  }
  
  public void newAmazon(String str) {
    this.amazonMap.put(str, new Amazon(str));
    this.tiles[0][0].addAmazon(this.amazonMap.get(str));
  }
  
  public HashMap<String, Amazon> getAmazonMap() {
    return this.amazonMap;
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
  
  public int getX() {
    return this.x;
  }
  
  public int getY() {
    return this.y;
  }
}
