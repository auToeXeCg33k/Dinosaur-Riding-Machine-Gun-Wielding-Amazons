package core;

import entities.Amazon;
import units.*;
import commands.*;
import items.*;

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
        this.players.put(true, new Player());
        this.players.put(false, new Player());

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
                return new Report("Világ létrehozva " + this.world.getSize() + "x" + this.world.getSize() + " mérettel.\n" +
                        "A maximális spawnok száma: " + this.maxSpawn + ", a játékosonként egyszerre élő amazonok maximális száma: " + this.maxActive + ".\n" +
                        "\nA help menü elérése: \"help\" parancs.\n", true);
            default:
                return new Report("Ilyen játékmód nincs is. Retry: ", false);
        }
    }
    public String nextMove() {
        this.moves++;
        return "\n---Még ennyiszer gyühetsz: " + (this.maxMoves - this.moves) + "---\n";
    }
    public void turn() {
        this.moves = 0;
        ((Select)this.commands.get("select")).clearSelection();
        this.playerMarker = !this.playerMarker;
    }


    public String newAmazon(String name) {
        this.players.get(this.playerMarker).addAmazon(name);
        if (playerMarker)
            this.world.getTiles()[this.world.getSize() - 1][this.world.getSize() - 1].add(this.players.get(this.playerMarker).getAmazon(name));
        else
            this.world.getTiles()[0][0].add(this.players.get(this.playerMarker).getAmazon(name));
        return name + " létrehozva az 1;1 mezőn.\n";
    }


    public Point location(Amazon a) {
        for (int i = 0; i < world.getTiles().length; i++)
            for (int j = 0; j < world.getTiles()[0].length; j++)
                if (world.getTiles()[i][j].contains((a)))
                    return new Point(j, i);
        return null;
    }
}