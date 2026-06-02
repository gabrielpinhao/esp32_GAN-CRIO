import tkinter as tk
import serial
import time

# --- CONFIGURAÇÃO DA PORTA SERIAL ---
PORTA_COM = 'COM8' 
VELOCIDADE = 115200

try:
    # Conecta ao ESP32
    esp32 = serial.Serial(PORTA_COM, VELOCIDADE)
    time.sleep(2) # Dá um tempinho para o ESP32 reiniciar após conectar
    print("Conectado ao ESP32 com sucesso!")
except Exception as e:
    print(f"Erro ao conectar na porta {PORTA_COM}. O cabo está ligado?")
    print(f"Erro detalhado: {e}")
    exit()

# --- FUNÇÕES DOS BOTÕES ---
def pulso():
    # Adicionado o \n no final para o ESP32 saber que a mensagem acabou
    esp32.write(b'1\n') 
    print("Comando pulso enviado.")

def desligar():
    esp32.write(b'0\n') 
    print("Comando DESLIGAR esp32 enviado.")

def ligar_esp32():
    esp32.write(b'2\n') 
    print("Comando LIGAR ESP32 enviado.")

def atualizar_tempo():
    # Pega o valor digitado na caixa de texto do Tkinter
    novo_tempo = entrada_tempo.get() 
    
    # Verifica se o usuário digitou apenas números
    if novo_tempo.isdigit():
        # Monta a string, ex: "T150\n" e converte para bytes (.encode)
        comando = f"T{novo_tempo}\n"
        esp32.write(comando.encode('utf-8'))
        print(f"Novo tempo de delay enviado: {novo_tempo} us")
    else:
        print("Erro: Digite apenas números inteiros para o tempo.")

# --- INTERFACE GRÁFICA (TKINTER) ---
janela = tk.Tk()
janela.title("Controle ESP32")
janela.geometry("300x250")

# Botões de controle básico
btn_ligar = tk.Button(janela, text="Ligar Saída (3.3V)", command=ligar_esp32, width=20)
btn_ligar.pack(pady=5)

btn_desligar = tk.Button(janela, text="Desligar Saída (0V)", command=desligar, width=20)
btn_desligar.pack(pady=5)

btn_pulso = tk.Button(janela, text="Enviar Pulso Rápido", command=pulso, width=20)
btn_pulso.pack(pady=5)

# --- SEÇÃO PARA ALTERAR O DELAY ---
# Cria um frame (uma "caixa") para organizar o texto, a entrada e o botão lado a lado
frame_tempo = tk.Frame(janela)
frame_tempo.pack(pady=15)

lbl_tempo = tk.Label(frame_tempo, text="Tempo (us):")
lbl_tempo.grid(row=0, column=0, padx=5)

# Caixa de texto para digitar o valor
entrada_tempo = tk.Entry(frame_tempo, width=8)
entrada_tempo.grid(row=0, column=1, padx=5)
entrada_tempo.insert(0, "80") # Deixa o valor 80 preenchido por padrão

# Botão para enviar o novo tempo
btn_atualizar = tk.Button(frame_tempo, text="Atualizar", command=atualizar_tempo)
btn_atualizar.grid(row=0, column=2, padx=5)

# --- FECHAMENTO SEGURO ---
# Garante que a porta serial seja fechada quando você fechar a janela no 'X'
def ao_fechar():
    print("Encerrando conexão e fechando o programa...")
    if esp32.is_open:
        esp32.close()
    janela.destroy()

janela.protocol("WM_DELETE_WINDOW", ao_fechar)

# Inicia o loop da interface gráfica
janela.mainloop()
