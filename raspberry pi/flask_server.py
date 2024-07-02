from flask import Flask, request, jsonify
from solana.rpc.api import Client
from solana.transaction import Transaction, TransactionInstruction
from solana.publickey import PublicKey
from solana.keypair import Keypair
import hashlib
import base58
import json

app = Flask(__name__)

# Connect to Solana Blockchain
solana_client = Client("https://api.devnet.solana.com")

# Load the keypair for the Raspberry Pi
with open('solana_keypair.json', 'r') as f:
    secret_key = json.load(f)
keypair = Keypair.from_secret_key(base58.b58decode(secret_key))

# Define the Solana program ID
program_id = PublicKey('YOUR_PROGRAM_ID')

@app.route('/data', methods=['POST'])
def receive_data():
    data = request.json
    patient_id = data['patient_id']
    ecg_data = data['ecg_data']

    # Serialize instruction data
    instruction_data = json.dumps({
        "patient_id": patient_id,
        "ecg_data": ecg_data
    }).encode()

    # Create the instruction
    instruction = TransactionInstruction(
        keys=[{'pubkey': keypair.public_key, 'is_signer': True, 'is_writable': True}],
        program_id=program_id,
        data=instruction_data
    )

    # Create and send the transaction
    transaction = Transaction().add(instruction)
    response = solana_client.send_transaction(transaction, keypair)

    print(f"Transaction response: {response}")
    return jsonify({'status': 'success', 'transaction': response})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)
